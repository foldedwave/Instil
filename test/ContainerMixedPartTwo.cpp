#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/ITestOne.h"
#include "TestTypes/ITestTwo.h"
#include "TestTypes/TestOne.h"
#include "TestTypes/TestTwo.h"

using Instil::Container;
using Instil::Scope;

TEST(Container, SingletonObjectWithTransientChildrenAreIdenticalInstances)
{
    auto testOne = Container<ITestTwo>::Get();
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_EQ(testOne, testTwo);
    EXPECT_EQ(testOne->GetOne(), testTwo->GetOne());
}

int main(int argc, char **argv)
{
    Container<ITestOne, TestOne>::Register(Scope::Transient);
    Container<ITestTwo, TestTwo, ITestOne>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}