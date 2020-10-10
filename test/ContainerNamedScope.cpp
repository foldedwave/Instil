#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/Interfaces/ISimple.h"
#include "TestTypes/Interfaces/IWrapSingle.h"
#include "TestTypes/Simple.h"
#include "TestTypes/WrapSingle.h"

using Instil::Container;
using Instil::Scope;

TEST(Container, ScopedObjectIsWellFormed)
{
    auto simple = Container<ISimple>::Get("TestScope");
    auto wrapSingle = Container<IWrapSingle>::Get("TestScope");

    EXPECT_EQ(simple->Call(), "Simple::Call()");
    EXPECT_EQ(wrapSingle->Call(), "WrapSingle::Call()");
}

TEST(Container, NamedScopeRequestForSameObjectReturnsSameInstance)
{
    auto simple1 = Container<ISimple>::Get("TestScope");
    auto simple2 = Container<ISimple>::Get("TestScope");

    EXPECT_EQ(simple1, simple2);
}

TEST(Container, NamedScopeRequestForSameObjectDifferentScopeReturnsDifferentInstance)
{
    auto simple1 = Container<ISimple>::Get("TestScope1");
    auto simple2 = Container<ISimple>::Get("TestScope2");

    EXPECT_NE(simple1, simple2);
}

TEST(Container, NamedScopeRequestForSameObjectDifferentScopeInHeirarchyReturnsDifferentInstance)
{
    auto simple = Container<ISimple>::Get("TestScope1");
    auto wrapSingle = Container<IWrapSingle>::Get("TestScope2");

    EXPECT_NE(simple, wrapSingle->GetSingle());
}

int main(int argc, char **argv)
{
    Container<ISimple>::For<Simple>::Register(Scope::Named);
    Container<IWrapSingle>::For<WrapSingle, ISimple>::Register(Scope::Named);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}