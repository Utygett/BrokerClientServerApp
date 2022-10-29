cmake_minimum_required(VERSION 3.23)
project(BrokerClientServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(Boost 1.80 COMPONENTS REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
find_package(qt5Widgets REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CLIENT_SRC
        src/Client/Client.cpp
        src/Client/login.cpp
        src/Client/mainwindow.cpp
        src/Client/tcpclient.cpp
        )

set(SERVER_SRC
        src/Server/Server.cpp
        src/Server/core.cpp
        src/Server/brocker/bid.cpp
        src/Server/brocker/currency.cpp
        src/Server/server/server.cpp
        src/Server/server/session.cpp
        )


add_executable(Client ${CLIENT_SRC})
target_link_libraries(Client ${Boost_LIBRARIES})
target_link_libraries(Client Qt5::Widgets)

add_executable(Server ${SERVER_SRC})
target_link_libraries(Server ${Boost_LIBRARIES})
