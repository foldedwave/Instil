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
    auto simple = Container<std::shared_ptr<ISimple>>::Get("TestScope");
    auto wrapSingle = Container<std::shared_ptr<IWrapSingle>>::Get("TestScope");

    EXPECT_EQ(simple->Call(), "Simple::Call()");
    EXPECT_EQ(wrapSingle->Call(), "WrapSingle::Call()");
}

TEST(Container, NamedScopeRequestForSameObjectReturnsSameInstance)
{
    auto simple1 = Container<std::shared_ptr<ISimple>>::Get("TestScope");
    auto simple2 = Container<std::shared_ptr<ISimple>>::Get("TestScope");

    EXPECT_EQ(simple1, simple2);
}

TEST(Container, NamedScopeRequestForSameObjectDifferentScopeReturnsDifferentInstance)
{
    auto simple1 = Container<std::shared_ptr<ISimple>>::Get("TestScope1");
    auto simple2 = Container<std::shared_ptr<ISimple>>::Get("TestScope2");

    EXPECT_NE(simple1, simple2);
}

TEST(Container, NamedScopeRequestForSameObjectDifferentScopeInHeirarchyReturnsDifferentInstance)
{
    auto simple = Container<std::shared_ptr<ISimple>>::Get("TestScope1");
    auto wrapSingle = Container<std::shared_ptr<IWrapSingle>>::Get("TestScope2");

    EXPECT_NE(simple, wrapSingle->GetSingle());
}

int main(int argc, char **argv)
{
    Container<std::shared_ptr<ISimple>>::For<std::shared_ptr<Simple>>::Register(Scope::Named);
    Container<std::shared_ptr<IWrapSingle>>::For<std::shared_ptr<WrapSingle>, std::shared_ptr<ISimple>>::Register(Scope::Named);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}