#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/ITestOne.h"
#include "TestTypes/ITestTwo.h"
#include "TestTypes/TestOne.h"
#include "TestTypes/TestTwo.h"

#include <memory>

using Instil::Container;
using Instil::Scope;

TEST(Container, TransientRequestForSameObjectReturnsDifferentInstance)
{
    auto testOne = Container<ITestOne>::Get();
    auto testTwo = Container<ITestOne>::Get();

    EXPECT_NE(testOne, testTwo);
}

TEST(Container, TransientRequestForObjectChildObjectsArePopulated)
{
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_TRUE(testTwo->GetOne() != nullptr);
}

TEST(Container, TransientRequestForSameObjectInHeirarchyReturnsDifferentInstance)
{
    auto testOne = Container<ITestOne>::Get();
    auto testTwo = Container<ITestTwo>::Get();

    EXPECT_NE(testOne, testTwo->GetOne());
}

int main(int argc, char **argv)
{
    Container<ITestOne, TestOne>::Register(Scope::Transient);
    Container<ITestTwo, TestTwo, ITestOne>::Register(Scope::Transient);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}