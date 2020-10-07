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

TEST(Container, MixedRegistrationObjectsAreWellFormed)
{
    auto simple = Container<ISimple>::Get();
    auto wrapSingle = Container<IWrapSingle>::Get();

    EXPECT_EQ(simple->Call(), "Simple::Call()");
    EXPECT_EQ(wrapSingle->Call(), "WrapSingle::Call()");
}

TEST(Container, TransientObjectWithSingletonChildrenContainIdenticalChildInstances)
{
    auto wrapSingle1 = Container<IWrapSingle>::Get();
    auto wrapSingle2 = Container<IWrapSingle>::Get();

    EXPECT_EQ(wrapSingle1->GetSingle(), wrapSingle2->GetSingle());
}

TEST(Container, TransientObjectWithSingletonChildrenAreDifferentInstances)
{
    auto wrapSingle1 = Container<IWrapSingle>::Get();
    auto wrapSingle2 = Container<IWrapSingle>::Get();

    EXPECT_NE(wrapSingle1, wrapSingle2);
}

int main(int argc, char **argv)
{
    Container<ISimple, Simple>::Register(Scope::Singleton);
    Container<IWrapSingle, WrapSingle, ISimple>::Register(Scope::Transient);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}