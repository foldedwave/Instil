#include <gtest/gtest.h>

#include <functional> // for __base, function
#include <memory>     // for shared_ptr
#include <string>     // for operator==

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/Interfaces/ISimple.h"
#include "TestTypes/Interfaces/IWrapSingle.h"
#include "TestTypes/Simple.h"
#include "TestTypes/WrapSingle.h"

using Instil::Container;
using Instil::Scope;

TEST(Container, SingletonObjectWithTransientChildrenAreIdenticalInstances)
{
    auto wrapSingle1 = Container<IWrapSingle>::Get();
    auto wrapSingle2 = Container<IWrapSingle>::Get();

    EXPECT_EQ(wrapSingle1, wrapSingle2);
    EXPECT_EQ(wrapSingle1->GetSingle(), wrapSingle2->GetSingle());
}

TEST(Container, TransientAndSingletonRegisteredSameClassesCreatesDifferentInstances)
{
    auto simple1 = Container<ISimple>::Get();
    auto simple2 = Container<ISimple2>::Get();

    void *v1 = simple1.get();
    void *v2 = simple2.get();

    EXPECT_NE(v1, v2);
}

int main(int argc, char **argv)
{
    Container<ISimple>::For<Simple>::Register(Scope::Transient);
    Container<ISimple2>::For<Simple>::Register(Scope::Singleton);
    Container<IWrapSingle>::For<WrapSingle, ISimple>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}