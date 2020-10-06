#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/ITestOne.h"
#include "TestTypes/ITestTwoAlternate.h"
#include "TestTypes/TestOne.h"
#include "TestTypes/TestOneAlternate.h"
#include "TestTypes/TestTwoAlternate.h"

using Instil::Container;
using Instil::Scope;

TEST(Container, VectorCtorParametersAreConstructable)
{
    EXPECT_NO_THROW(Container<ITestTwoAlternate>::Get());
}

TEST(Container, VectorContainsCorrectObjects)
{
    auto testTwo = Container<ITestTwoAlternate>::Get();

    EXPECT_EQ(testTwo->Call1(), "TestTwoAlternate::Call1()");
    EXPECT_EQ(testTwo->CallChild(), "TestOne::Call1()/TestOneAlternate::Call1()/");
}

TEST(Container, VectorObjectReferenceCountsAreCorrect)
{
    auto testTwo = Container<ITestTwoAlternate>::Get();

    EXPECT_EQ(testTwo.use_count(), 2);
    EXPECT_EQ(testTwo->GetOne()[0].use_count(), 3);
    EXPECT_EQ(testTwo->GetOne()[1].use_count(), 3);
}

int main(int argc, char **argv)
{
    Container<ITestOne, TestOne>::Register(Scope::Singleton);
    Container<ITestOne, TestOneAlternate>::Register(Scope::Singleton);
    Container<ITestTwoAlternate, TestTwoAlternate, std::vector<ITestOne>>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}