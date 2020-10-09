#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/Interfaces/ISimple.h"
#include "TestTypes/Simple.h"
#include "TestTypes/SimpleAlternate.h"

#include <memory>

using Instil::Container;
using Instil::Scope;

TEST(Container, MultipleRegistrationObjectsAreWellFormed)
{
    auto simpleCollection = Container<std::shared_ptr<ISimple>>::GetAll();

    EXPECT_EQ(simpleCollection[0]->Call(), "Simple::Call()");
    EXPECT_EQ(simpleCollection[1]->Call(), "SimpleAlternate::Call()");
}

TEST(Container, MultipleRegistrationDefaultGetReturnsSameInstance)
{
    auto simple1 = Container<std::shared_ptr<ISimple>>::Get();
    auto simple2 = Container<std::shared_ptr<ISimple>>::Get();

    EXPECT_EQ(simple1, simple2);
}

TEST(Container, MultipleRegistrationGetAllReturnsAllInstances)
{
    auto simpleCollection = Container<std::shared_ptr<ISimple>>::GetAll();

    simpleCollection[0]->Call();
    simpleCollection[1]->Call();

    EXPECT_EQ(simpleCollection.size(), 2);
}

int main(int argc, char **argv)
{
    Container<std::shared_ptr<ISimple>>::For<std::shared_ptr<Simple>>::Register(Scope::Singleton);
    Container<std::shared_ptr<ISimple>>::For<std::shared_ptr<SimpleAlternate>>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}