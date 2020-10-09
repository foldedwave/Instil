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
    auto simple = Container<std::shared_ptr<ISimple>>::Get();

    EXPECT_EQ(simple.use_count(), 2);
}

TEST(Container, SingletonFirstCompositeObjectHasCorrectRefCount)
{
    auto wrapSingle = Container<std::shared_ptr<IWrapSingle>>::Get();

    EXPECT_EQ(wrapSingle.use_count(), 2);
    EXPECT_EQ(wrapSingle->GetSingle().use_count(), 3);
}

TEST(Container, SingletonCompositeObjectRetainsReferenceEvenWhenNoneAreInScope)
{
    auto simple = Container<std::shared_ptr<ISimple>>::Get();

    EXPECT_EQ(simple.use_count(), 3);
}

TEST(Container, SingletonObjectIsWellFormed)
{
    auto simple = Container<std::shared_ptr<ISimple>>::Get();
    auto wrapSingle = Container<std::shared_ptr<IWrapSingle>>::Get();

    EXPECT_EQ(simple->Call(), "Simple::Call()");
    EXPECT_EQ(wrapSingle->Call(), "WrapSingle::Call()");
}

TEST(Container, SingletonRequestForSameObjectReturnsSameInstance)
{
    auto simple1 = Container<std::shared_ptr<ISimple>>::Get();
    auto simple2 = Container<std::shared_ptr<ISimple>>::Get();

    EXPECT_EQ(simple1.use_count(), 4);
    EXPECT_EQ(simple1, simple2);
}

TEST(Container, SingletonRequestForObjectChildObjectsArePopulated)
{
    auto wrapSingle = Container<std::shared_ptr<IWrapSingle>>::Get();

    EXPECT_EQ(wrapSingle.use_count(), 2);
    EXPECT_EQ(wrapSingle->GetSingle().use_count(), 3);
    EXPECT_TRUE(wrapSingle->GetSingle() != nullptr);
}

TEST(Container, SingletonRequestForSameObjectInHeirarchyReturnsSameInstance)
{
    auto simple = Container<std::shared_ptr<ISimple>>::Get();
    auto wrapSingle = Container<std::shared_ptr<IWrapSingle>>::Get();

    EXPECT_EQ(simple.use_count(), 3);
    EXPECT_EQ(wrapSingle->GetSingle().use_count(), 4);
    EXPECT_EQ(wrapSingle.use_count(), 2);
    EXPECT_EQ(simple, wrapSingle->GetSingle());
}

TEST(Container, SeeHowManyTimes)
{
    auto simple1 = Container<std::shared_ptr<ISimple>>::Get();
    auto simple2 = Container<std::shared_ptr<ISimple2>>::Get();
    
    void* v1 = simple1.get();
    void* v2 = simple1.get();

    EXPECT_EQ(v1, v2);
}

int main(int argc, char **argv)
{
    Container<std::shared_ptr<ISimple>>::For<std::shared_ptr<Simple>>::Register(Scope::Singleton);
    Container<std::shared_ptr<ISimple2>>::For<std::shared_ptr<Simple>>::Register(Scope::Singleton);
    Container<std::shared_ptr<IWrapSingle>>::For<std::shared_ptr<WrapSingle>, std::shared_ptr<ISimple>>::Register(Scope::Singleton);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}