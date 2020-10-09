#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/Interfaces/ISimple.h"
#include "TestTypes/Interfaces/IWrapSingle.h"
#include "TestTypes/Simple.h"
#include "TestTypes/WrapSingle.h"

using Instil::Container;
using Instil::Scope;

TEST(Container, MixedRegistrationObjectsAreWellFormed)
{
    auto simple = Container<std::shared_ptr<ISimple>>::Get();
    auto wrapSingle = Container<std::shared_ptr<IWrapSingle>>::Get();

    EXPECT_EQ(simple->Call(), "Simple::Call()");
    EXPECT_EQ(wrapSingle->Call(), "WrapSingle::Call()");
}

TEST(Container, SingletonObjectsRelatedToTransientObjectsAreIdentical)
{
    auto simple1 = Container<std::shared_ptr<ISimple>>::Get();
    auto simple2 = Container<std::shared_ptr<ISimple>>::Get();

    EXPECT_EQ(simple1, simple2);
}

TEST(Container, TransientObjectsRelatedToSingletonObjectsAreDifferent)
{
    auto simple1 = Container<std::shared_ptr<ISimple2>>::Get();
    auto simple2 = Container<std::shared_ptr<ISimple2>>::Get();

    EXPECT_NE(simple1, simple2);
}

TEST(Container, TransientObjectWithSingletonChildrenContainIdenticalChildInstances)
{
    auto wrapSingle1 = Container<std::shared_ptr<IWrapSingle>>::Get();
    auto wrapSingle2 = Container<std::shared_ptr<IWrapSingle>>::Get();

    EXPECT_EQ(wrapSingle1->GetSingle(), wrapSingle2->GetSingle());
}

TEST(Container, TransientObjectWithSingletonChildrenAreDifferentInstances)
{
    auto wrapSingle1 = Container<std::shared_ptr<IWrapSingle>>::Get();
    auto wrapSingle2 = Container<std::shared_ptr<IWrapSingle>>::Get();

    EXPECT_NE(wrapSingle1, wrapSingle2);
}

TEST(Container, SingletonAndTransientRegisteredSameClassesCreatesDifferentInstances)
{
    auto simple1 = Container<std::shared_ptr<ISimple>>::Get();
    auto simple2 = Container<std::shared_ptr<ISimple2>>::Get();

    void* v1 = simple1.get();
    void* v2 = simple2.get();

    EXPECT_NE(v1, v2);
}

int main(int argc, char **argv)
{
    Container<std::shared_ptr<ISimple>>::For<std::shared_ptr<Simple>>::Register(Scope::Singleton);
    Container<std::shared_ptr<ISimple2>>::For<std::shared_ptr<Simple>>::Register(Scope::Transient);
    Container<std::shared_ptr<IWrapSingle>>::For<std::shared_ptr<WrapSingle>, std::shared_ptr<ISimple>>::Register(Scope::Transient);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}