#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/Interfaces/ISimple.h"
#include "TestTypes/Interfaces/IWrapMultiple.h"
#include "TestTypes/Simple.h"
#include "TestTypes/SimpleAlternate.h"
#include "TestTypes/WrapMultiple.h"

#include <utility>
#include <memory>

using Instil::Container;
using Instil::Scope;

TEST(Container, VectorContainsCorrectObjects)
{
    auto wrapMulti = Container<IWrapMultiple>::Get();

    EXPECT_EQ(wrapMulti->Call(), "WrapMultiple::Call()");
    EXPECT_EQ(wrapMulti->CallChildren(), "Simple::Call()/SimpleAlternate::Call()/");
}

TEST(Container, VectorObjectReferenceCountsAreCorrect)
{
    auto wrapMulti = Container<IWrapMultiple>::Get();

    EXPECT_EQ(wrapMulti.use_count(), 2);
    EXPECT_EQ(wrapMulti->GetAll()[0].use_count(), 3);
    EXPECT_EQ(wrapMulti->GetAll()[1].use_count(), 3);
}

int main(int argc, char **argv)
{
    Container<ISimple>::For<Simple>::Register(Scope::Singleton);
    Container<ISimple>::For<SimpleAlternate>::Register(Scope::Singleton);
    Container<IWrapMultiple>::For<WrapMultiple, std::vector<ISimple>>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}