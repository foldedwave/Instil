#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/TypeInfo.h"  // for REGISTER_PARSE_TYPE
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/ITestOne.h"
#include "TestTypes/ITestTwo.h"
#include "TestTypes/TestOne.h"
#include "TestTypes/TestTwo.h"

REGISTER_TYPE_INFO(ITestOne);
REGISTER_TYPE_INFO(ITestTwo);
REGISTER_TYPE_INFO(TestOne);
REGISTER_TYPE_INFO(TestTwo);

TEST(Container, TransientObjectWithSingletonChildrenContainIdenticalChildInstances)
{
    Container<ITestOne, TestOne>::Register(Scope::Singleton);
    Container<ITestTwo, TestTwo, ITestOne>::Register(Scope::Transient);

    auto testOne = Container<ITestTwo>::Get();
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_EQ(testOne->GetOne(), testTwo->GetOne());
}

TEST(Container, TransientObjectWithSingletonChildrenAreDifferentInstances)
{
    Container<ITestOne, TestOne>::Register(Scope::Singleton);
    Container<ITestTwo, TestTwo, ITestOne>::Register(Scope::Transient);

    auto testOne = Container<ITestTwo>::Get();
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_NE(testOne, testTwo);
}

TEST(Container, SingletonObjectWithTransientChildrenAreIdenticalInstances)
{
    Container<ITestOne, TestOne>::Register(Scope::Transient);
    Container<ITestTwo, TestTwo, ITestOne>::Register(Scope::Singleton);

    auto testOne = Container<ITestTwo>::Get();
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_EQ(testOne, testTwo);
    EXPECT_EQ(testOne->GetOne(), testTwo->GetOne());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}