cmake_minimum_required(VERSION 3.23)
project(BrokerServer)


FIND_PACKAGE(Boost 1.80 COMPONENTS REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
find_package(qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CLIENT_SRC
        ${PROJECT_SOURCE_DIR}/Client.cpp
        ${PROJECT_SOURCE_DIR}/login.cpp
        ${PROJECT_SOURCE_DIR}/mainwindow.cpp
        ${PROJECT_SOURCE_DIR}/tcpclient.cpp
        )

add_executable(Client ${CLIENT_SRC})
target_link_libraries(Client ${Boost_LIBRARIES})
target_link_libraries(Client Qt5::Widgets)