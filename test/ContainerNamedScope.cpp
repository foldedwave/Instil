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

TEST(Container, NamedScopeRequestForSameObjectReturnsSameInstance)
{
    Container<ITestOne, TestOne>::Register(Scope::Named);

    auto testOne = Container<ITestOne>::Get("TestScope");
    auto testTwo = Container<ITestOne>::Get("TestScope");

    EXPECT_EQ(testOne, testTwo);
}

TEST(Container, NamedScopeRequestForSameObjectDifferentScopeReturnsDifferentInstance)
{
    Container<ITestOne, TestOne>::Register(Scope::Named);

    auto testOne = Container<ITestOne>::Get("TestScope1");
    auto testTwo = Container<ITestOne>::Get("TestScope2");

    EXPECT_NE(testOne, testTwo);
}

TEST(Container, NamedScopeRequestForSameObjectDifferentScopeInHeirarchyReturnsDifferentInstance)
{
    Container<ITestOne, TestOne>::Register(Scope::Named);
    Container<ITestTwo, TestTwo, ITestOne>::Register(Scope::Named);

    auto testOne = Container<ITestOne>::Get("TestScope1");
    auto testTwo = Container<ITestTwo>::Get("TestScope2");

    EXPECT_NE(testOne, testTwo->GetOne());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}