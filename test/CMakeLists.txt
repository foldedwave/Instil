add_executable(ContainerSingleton ContainerSingleton.cpp TestTypes/TestOne.cpp TestTypes/TestTwo.cpp)
target_link_libraries(ContainerSingleton PRIVATE InstilLib)
target_link_libraries(ContainerSingleton PRIVATE gtest)

add_test(NAME ContainerSingleton COMMAND ContainerSingleton)

add_executable(ContainerTransient ContainerTransient.cpp TestTypes/TestOne.cpp TestTypes/TestTwo.cpp)
target_link_libraries(ContainerTransient PRIVATE InstilLib)
target_link_libraries(ContainerTransient PRIVATE gtest)

add_test(NAME ContainerTransient COMMAND ContainerTransient)

add_executable(ContainerMixed ContainerMixed.cpp TestTypes/TestOne.cpp TestTypes/TestTwo.cpp)
target_link_libraries(ContainerMixed PRIVATE InstilLib)
target_link_libraries(ContainerMixed PRIVATE gtest)

add_test(NAME ContainerMixed COMMAND ContainerMixed)

add_executable(ContainerNamedScope ContainerNamedScope.cpp TestTypes/TestOne.cpp TestTypes/TestTwo.cpp)
target_link_libraries(ContainerNamedScope PRIVATE InstilLib)
target_link_libraries(ContainerNamedScope PRIVATE gtest)

add_test(NAME ContainerNamedScope COMMAND ContainerNamedScope)