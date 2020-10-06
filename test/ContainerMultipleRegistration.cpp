#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/ITestOne.h"
#include "TestTypes/TestOne.h"
#include "TestTypes/TestOneAlternate.h"

#include <memory>

using Instil::Container;
using Instil::Scope;


TEST(Container, MultipleRegistrationObjectsAreWellFormed)
{
    auto testAllOnes = Container<ITestOne>::GetAll();

    EXPECT_EQ(testAllOnes.at(0)->Call1(), "TestOne::Call1()");
    EXPECT_EQ(testAllOnes.at(1)->Call1(), "TestOneAlternate::Call1()");
}

TEST(Container, MultipleRegistrationDefaultGetReturnsSameInstance)
{
    auto testOne = Container<ITestOne>::Get();
    auto testTwo = Container<ITestOne>::Get();

    EXPECT_EQ(testOne, testTwo);
}

TEST(Container, MultipleRegistrationGetAllReturnsAllInstances)
{
    auto testAllOnes = Container<ITestOne>::GetAll();

    testAllOnes.at(0)->Call1();
    testAllOnes.at(1)->Call1();

    EXPECT_EQ(testAllOnes.size(), 2);
}

int main(int argc, char **argv)
{
    Container<ITestOne, TestOne>::Register(Scope::Singleton);
    Container<ITestOne, TestOneAlternate>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}