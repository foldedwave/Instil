#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/Interfaces/ISimple.h"
#include "TestTypes/Interfaces/IWrapMultiple.h"
#include "TestTypes/Simple.h"
#include "TestTypes/SimpleAlternate.h"
#include "TestTypes/WrapMultipleAsMap.h"

#include <utility>
#include <memory>
#include <map>

using Instil::Container;
using Instil::Scope;

TEST(Container, MapContainsCorrectObjects)
{
    auto wrapMulti = Container<IWrapMultipleAsMap>::Get();

    EXPECT_EQ(wrapMulti->Call(), "WrapMultipleAsMap::Call()");
    EXPECT_EQ(wrapMulti->CallChildren(), "Simple::Call()/SimpleAlternate::Call()/");
}

TEST(Container, MapObjectReferenceCountsAreCorrect)
{
    auto wrapMulti = Container<IWrapMultipleAsMap>::Get();

    EXPECT_EQ(wrapMulti.use_count(), 2);
    EXPECT_EQ(wrapMulti->GetAll()["Simple"].use_count(), 3);
    EXPECT_EQ(wrapMulti->GetAll()["SimpleAlternate"].use_count(), 3);
}

int main(int argc, char **argv)
{
    Container<ISimple>::For<Simple>::Register(Scope::Singleton, "Simple");
    Container<ISimple>::For<SimpleAlternate>::Register(Scope::Singleton, "SimpleAlternate");
    Container<IWrapMultipleAsMap>::For<WrapMultipleAsMap, std::map<string, ISimple>>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}