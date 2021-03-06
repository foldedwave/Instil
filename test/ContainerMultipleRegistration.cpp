#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/Interfaces/ISimple.h"
#include "TestTypes/Simple.h"
#include "TestTypes/SimpleAlternate.h"

#include <memory>
#include <string>                          // for operator==
#include <vector>                          // for vector

using Instil::Container;
using Instil::Scope;

TEST(Container, MultipleRegistrationObjectsAreWellFormed)
{
    auto simpleCollection = Container<ISimple>::GetAll();

    EXPECT_EQ(simpleCollection[0]->Call(), "Simple::Call()");
    EXPECT_EQ(simpleCollection[1]->Call(), "SimpleAlternate::Call()");
}

TEST(Container, MultipleRegistrationDefaultGetReturnsSameInstance)
{
    auto simple1 = Container<ISimple>::Get();
    auto simple2 = Container<ISimple>::Get();

    EXPECT_EQ(simple1, simple2);
}

TEST(Container, MultipleRegistrationGetAllReturnsAllInstances)
{
    auto simpleCollection = Container<ISimple>::GetAll();

    simpleCollection[0]->Call();
    simpleCollection[1]->Call();

    EXPECT_EQ(simpleCollection.size(), 2);
}

int main(int argc, char **argv)
{
    Container<ISimple>::For<Simple>::Register(Scope::Singleton);
    Container<ISimple>::For<SimpleAlternate>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}