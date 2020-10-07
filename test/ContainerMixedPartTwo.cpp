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

TEST(Container, SingletonObjectWithTransientChildrenAreIdenticalInstances)
{
    auto wrapSingle1 = Container<IWrapSingle>::Get();
    auto wrapSingle2 = Container<IWrapSingle>::Get();

    EXPECT_EQ(wrapSingle1, wrapSingle2);
    EXPECT_EQ(wrapSingle1->GetSingle(), wrapSingle2->GetSingle());
}

int main(int argc, char **argv)
{
    Container<ISimple, Simple>::Register(Scope::Transient);
    Container<IWrapSingle, WrapSingle, ISimple>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}