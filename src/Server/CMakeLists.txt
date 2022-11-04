cmake_minimum_required(VERSION 3.23)
project(BrokerClient)

FIND_PACKAGE(Boost 1.80 COMPONENTS REQUIRED)
set(SERVER_SRC
        ${PROJECT_SOURCE_DIR}/Server.cpp
        ${PROJECT_SOURCE_DIR}/core.cpp
        ${PROJECT_SOURCE_DIR}/brocker/bid.cpp
        ${PROJECT_SOURCE_DIR}/brocker/currency.cpp
        ${PROJECT_SOURCE_DIR}/server/server.cpp
        ${PROJECT_SOURCE_DIR}/server/session.cpp
        )

add_executable(Server ${SERVER_SRC})
target_link_libraries(Server ${Boost_LIBRARIES})