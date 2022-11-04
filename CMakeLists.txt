cmake_minimum_required(VERSION 3.23)
project(BrokerClientServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


#INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIR})
include_directories(include)

add_subdirectory(src/Client)
add_subdirectory(src/Server)
add_subdirectory(lib/googletest-release-1.12.1)
add_subdirectory(test/Client)
add_subdirectory(test/Server)


