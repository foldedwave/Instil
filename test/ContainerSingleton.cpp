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

TEST(Container, SingletonFirstSingleObjectHasCorrectRefCount)
{
    auto simple = Container<ISimple>::Get();

    EXPECT_EQ(simple.use_count(), 2);
}

TEST(Container, SingletonFirstCompositeObjectHasCorrectRefCount)
{
    auto wrapSingle = Container<IWrapSingle>::Get();

    EXPECT_EQ(wrapSingle.use_count(), 2);
    EXPECT_EQ(wrapSingle->GetSingle().use_count(), 3);
}

TEST(Container, SingletonCompositeObjectRetainsReferenceEvenWhenNoneAreInScope)
{
    auto simple = Container<ISimple>::Get();

    EXPECT_EQ(simple.use_count(), 3);
}

TEST(Container, SingletonObjectIsWellFormed)
{
    auto simple = Container<ISimple>::Get();
    auto wrapSingle = Container<IWrapSingle>::Get();

    EXPECT_EQ(simple->Call(), "Simple::Call()");
    EXPECT_EQ(wrapSingle->Call(), "WrapSingle::Call()");
}

TEST(Container, SingletonRequestForSameObjectReturnsSameInstance)
{
    auto simple1 = Container<ISimple>::Get();
    auto simple2 = Container<ISimple>::Get();

    EXPECT_EQ(simple1.use_count(), 4);
    EXPECT_EQ(simple1, simple2);
}

TEST(Container, SingletonRequestForObjectChildObjectsArePopulated)
{
    auto wrapSingle = Container<IWrapSingle>::Get();

    EXPECT_EQ(wrapSingle.use_count(), 2);
    EXPECT_EQ(wrapSingle->GetSingle().use_count(), 3);
    EXPECT_TRUE(wrapSingle->GetSingle() != nullptr);
}

TEST(Container, SingletonRequestForSameObjectInHeirarchyReturnsSameInstance)
{
    auto simple = Container<ISimple>::Get();
    auto wrapSingle = Container<IWrapSingle>::Get();

    EXPECT_EQ(simple.use_count(), 3);
    EXPECT_EQ(wrapSingle->GetSingle().use_count(), 4);
    EXPECT_EQ(wrapSingle.use_count(), 2);
    EXPECT_EQ(simple, wrapSingle->GetSingle());
}

TEST(Container, SeeHowManyTimes)
{
    auto simple1 = Container<ISimple>::Get();
    auto simple2 = Container<ISimple>::Get();
}

int main(int argc, char **argv)
{
    Container<ISimple, Simple>::Register(Scope::Singleton);
    Container<IWrapSingle, WrapSingle, ISimple>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}