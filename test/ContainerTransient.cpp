#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/Interfaces/ISimple.h"
#include "TestTypes/Interfaces/IWrapSingle.h"
#include "TestTypes/Simple.h"
#include "TestTypes/WrapSingle.h"

#include <memory>

using Instil::Container;
using Instil::Scope;

TEST(Container, TransientObjectIsWellFormed)
{
    auto simple = Container<std::shared_ptr<ISimple>>::Get();
    auto wrapSingle = Container<std::shared_ptr<IWrapSingle>>::Get();

    EXPECT_EQ(simple->Call(), "Simple::Call()");
    EXPECT_EQ(wrapSingle->Call(), "WrapSingle::Call()");
}

TEST(Container, TransientRequestForSameObjectReturnsDifferentInstance)
{
    auto simple1 = Container<std::shared_ptr<ISimple>>::Get();
    auto simple2 = Container<std::shared_ptr<ISimple>>::Get();

    EXPECT_NE(simple1, simple2);
}

TEST(Container, TransientRequestForObjectChildObjectsArePopulated)
{
    auto wrapSingle = Container<std::shared_ptr<IWrapSingle>>::Get();

    EXPECT_TRUE(wrapSingle->GetSingle() != nullptr);
}

TEST(Container, TransientRequestForSameObjectInHeirarchyReturnsDifferentInstance)
{
    auto simple = Container<std::shared_ptr<ISimple>>::Get();
    auto wrapSingle = Container<std::shared_ptr<IWrapSingle>>::Get();

    EXPECT_NE(simple, wrapSingle->GetSingle());
}

int main(int argc, char **argv)
{
    Container<std::shared_ptr<ISimple>>::For<std::shared_ptr<Simple>>::Register(Scope::Transient);
    Container<std::shared_ptr<IWrapSingle>>::For<std::shared_ptr<WrapSingle>, std::shared_ptr<ISimple>>::Register(Scope::Transient);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}