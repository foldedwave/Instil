#include <gtest/gtest.h>

#include <functional> // for __base, function

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

#include "TestTypes/Interfaces/ITemplated.h"
#include "TestTypes/Templated.h"

using Instil::Container;
using Instil::Scope;

TEST(Container, ContainerRetrievesTemplateOfRegisteredType)
{
    auto simple = Container<ITemplated<int>>::Get();

    EXPECT_EQ(simple.use_count(), 2);
}

// TEST(Container, ContainerThrowsWhenNonRegisteredTemplateIsRequested)
// {
//     EXPECT_ANY_THROW(
//         Container<ITemplated<double>>::Get();
//     );
// }

int main(int argc, char **argv)
{
    Container<ITemplated<int>>::For<Templated<int>>::Register(Scope::Singleton, "ITemplated<int>");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}