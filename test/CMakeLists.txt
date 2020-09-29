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


add_executable(ContainerSingleton ContainerSingleton.cpp TestTypes/TestOne.cpp TestTypes/TestTwo.cpp)
target_link_libraries(ContainerSingleton PRIVATE InstilLib)
target_link_libraries(ContainerSingleton PRIVATE gtest gmock)
add_test(NAME ContainerSingleton COMMAND ContainerSingleton)

add_executable(ContainerTransient ContainerTransient.cpp TestTypes/TestOne.cpp TestTypes/TestTwo.cpp)
target_link_libraries(ContainerTransient PRIVATE InstilLib)
target_link_libraries(ContainerTransient PRIVATE gtest gmock)
add_test(NAME ContainerTransient COMMAND ContainerTransient)

add_executable(ContainerMixed ContainerMixed.cpp TestTypes/TestOne.cpp TestTypes/TestTwo.cpp)
target_link_libraries(ContainerMixed PRIVATE InstilLib)
target_link_libraries(ContainerMixed PRIVATE gtest gmock)
add_test(NAME ContainerMixed COMMAND ContainerMixed)

add_executable(ContainerNamedScope ContainerNamedScope.cpp TestTypes/TestOne.cpp TestTypes/TestTwo.cpp)
target_link_libraries(ContainerNamedScope PRIVATE InstilLib)
target_link_libraries(ContainerNamedScope PRIVATE gtest gmock)
add_test(NAME ContainerNamedScope COMMAND ContainerNamedScope)