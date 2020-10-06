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

TEST(Container, SingletonFirstSingleObjectHasCorrectRefCount)
{
    auto testOne = Container<ITestOne>::Get();

    EXPECT_EQ(testOne.use_count(), 2);
}

TEST(Container, SingletonFirstCompositeObjectHasCorrectRefCount)
{
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_EQ(testTwo.use_count(), 2);
    EXPECT_EQ(testTwo->GetOne().use_count(), 3);
}

TEST(Container, SingletonCompositeObjectRetainsReferenceEvenWhenNoneAreInScope)
{
    auto testOne = Container<ITestOne>::Get();

    EXPECT_EQ(testOne.use_count(), 3);
}

TEST(Container, SingletonObjectIsWellFormed)
{
    auto testOne = Container<ITestOne>::Get();
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_EQ(testOne->Call1(), "TestOne::Call1()");
    EXPECT_EQ(testTwo->Call1(), "TestTwo::Call1()");
}

TEST(Container, SingletonRequestForSameObjectReturnsSameInstance)
{
    auto testOne = Container<ITestOne>::Get();
    auto testTwo = Container<ITestOne>::Get();

    EXPECT_EQ(testOne.use_count(), 4);
    EXPECT_EQ(testOne, testTwo);
}

TEST(Container, SingletonRequestForObjectChildObjectsArePopulated)
{
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_EQ(testTwo.use_count(), 2);
    EXPECT_EQ(testTwo->GetOne().use_count(), 3);
    EXPECT_TRUE(testTwo->GetOne() != nullptr);
}

TEST(Container, SingletonRequestForSameObjectInHeirarchyReturnsSameInstance)
{
    auto testOne = Container<ITestOne>::Get();
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_EQ(testOne.use_count(), 3);
    EXPECT_EQ(testTwo->GetOne().use_count(), 4);
    EXPECT_EQ(testTwo.use_count(), 2);
    EXPECT_EQ(testOne, testTwo->GetOne());
}

TEST(Container, SeeHowManyTimes)
{
    auto testOne = Container<ITestOne>::Get();
    auto testTwo = Container<ITestOne>::Get();
}

int main(int argc, char **argv)
{
    Container<ITestOne, TestOne>::Register(Scope::Singleton);
    Container<ITestTwo, TestTwo, ITestOne>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}