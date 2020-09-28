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

TEST(Container, SingletonRequestForSameObjectReturnsSameInstance)
{
    Container<ITestOne, TestOne>::Register(Scope::Singleton);

    auto testOne = Container<ITestOne>::Get();
    auto testTwo = Container<ITestOne>::Get();

    EXPECT_EQ(testOne.use_count(), 3);
    EXPECT_EQ(testOne, testTwo);
}

TEST(Container, SingletonRequestForObjectChildObjectsArePopulated)
{
    Container<ITestOne, TestOne>::Register(Scope::Singleton);
    Container<ITestTwo, TestTwo, ITestOne>::Register(Scope::Singleton);

    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_EQ(testTwo.use_count(), 2);
    EXPECT_EQ(testTwo->GetOne().use_count(), 3);
    EXPECT_TRUE(testTwo->GetOne() != nullptr);
}

TEST(Container, SingletonRequestForSameObjectInHeirarchyReturnsSameInstance)
{
    Container<ITestOne, TestOne>::Register(Scope::Singleton);
    Container<ITestTwo, TestTwo, ITestOne>::Register(Scope::Singleton);

    auto testOne = Container<ITestOne>::Get();
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_EQ(testOne.use_count(), 3);
    EXPECT_EQ(testTwo->GetOne().use_count(), 4);
    EXPECT_EQ(testTwo.use_count(), 2);
    EXPECT_EQ(testOne, testTwo->GetOne());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}