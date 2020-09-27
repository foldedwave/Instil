cmake_minimum_required(VERSION 3.17.0)
project(Instil VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(IWYU_PATH NAMES include-what-you-use iwyu)
if(NOT IWYU_PATH)
  message(WARNING "Could not find the program include-what-you-use")
else()
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})
endif()

# include(CTest)
# enable_testing()

add_subdirectory(src)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    enable_testing()
    add_subdirectory(test)

endif()

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)