cmake_minimum_required(VERSION 3.14)
project(mini_kv CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_library(kvlib src/Database.cpp src/Storage.cpp)
target_include_directories(kvlib PUBLIC include)

add_executable(mini-kv src/main.cpp)
target_link_libraries(mini-kv kvlib)

enable_testing()
add_executable(test_database tests/test_database.cpp)
target_link_libraries(test_database kvlib)
add_test(NAME database COMMAND test_database)
