include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG "release-1.10.0"
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  set(INSTALL_GTEST
  CACHE BOOL
  OFF)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()


add_executable(ContainerSingleton ContainerSingleton.cpp TestTypes/Simple.cpp TestTypes/WrapSingle.cpp)
target_link_libraries(ContainerSingleton PRIVATE InstilLib)
target_link_libraries(ContainerSingleton PRIVATE gtest gmock)
add_test(NAME ContainerSingleton COMMAND ContainerSingleton)

add_executable(ContainerTransient ContainerTransient.cpp TestTypes/Simple.cpp TestTypes/WrapSingle.cpp)
target_link_libraries(ContainerTransient PRIVATE InstilLib)
target_link_libraries(ContainerTransient PRIVATE gtest gmock)
add_test(NAME ContainerTransient COMMAND ContainerTransient)

add_executable(ContainerMixed ContainerMixed.cpp TestTypes/Simple.cpp TestTypes/WrapSingle.cpp)
target_link_libraries(ContainerMixed PRIVATE InstilLib)
target_link_libraries(ContainerMixed PRIVATE gtest gmock)
add_test(NAME ContainerMixed COMMAND ContainerMixed)

add_executable(ContainerMixedPartTwo ContainerMixedPartTwo.cpp TestTypes/Simple.cpp TestTypes/WrapSingle.cpp)
target_link_libraries(ContainerMixedPartTwo PRIVATE InstilLib)
target_link_libraries(ContainerMixedPartTwo PRIVATE gtest gmock)
add_test(NAME ContainerMixedPartTwo COMMAND ContainerMixedPartTwo)

add_executable(ContainerNamedScope ContainerNamedScope.cpp TestTypes/Simple.cpp TestTypes/WrapSingle.cpp)
target_link_libraries(ContainerNamedScope PRIVATE InstilLib)
target_link_libraries(ContainerNamedScope PRIVATE gtest gmock)
add_test(NAME ContainerNamedScope COMMAND ContainerNamedScope)

add_executable(ContainerMultipleRegistration ContainerMultipleRegistration.cpp TestTypes/Simple.cpp TestTypes/SimpleAlternate.cpp)
target_link_libraries(ContainerMultipleRegistration PRIVATE InstilLib)
target_link_libraries(ContainerMultipleRegistration PRIVATE gtest gmock)
add_test(NAME ContainerMultipleRegistration COMMAND ContainerMultipleRegistration)

add_executable(ContainerVectors ContainerVectors.cpp TestTypes/Simple.cpp TestTypes/SimpleAlternate.cpp TestTypes/WrapMultiple.cpp)
target_link_libraries(ContainerVectors PRIVATE InstilLib)
target_link_libraries(ContainerVectors PRIVATE gtest gmock)
add_test(NAME ContainerVectors COMMAND ContainerVectors)

add_executable(ContainerMaps ContainerMaps.cpp TestTypes/Simple.cpp TestTypes/SimpleAlternate.cpp TestTypes/WrapMultipleAsMap.cpp)
target_link_libraries(ContainerMaps PRIVATE InstilLib)
target_link_libraries(ContainerMaps PRIVATE gtest gmock)
add_test(NAME ContainerMaps COMMAND ContainerMaps)

add_executable(ContainerTemplated ContainerTemplated.cpp)
target_link_libraries(ContainerTemplated PRIVATE InstilLib)
target_link_libraries(ContainerTemplated PRIVATE gtest gmock)
add_test(NAME ContainerTemplated COMMAND ContainerTemplated)