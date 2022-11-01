FIND_PACKAGE(Boost 1.80 COMPONENTS REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
find_package(qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CLIENT_SRC
        ${PROJECT_SOURCE_DIR}/src/Client/Client.cpp
        ${PROJECT_SOURCE_DIR}/src/Client/login.cpp
        ${PROJECT_SOURCE_DIR}/src/Client/mainwindow.cpp
        ${PROJECT_SOURCE_DIR}/src/Client/tcpclient.cpp
        )

add_executable(Client ${CLIENT_SRC})
target_link_libraries(Client ${Boost_LIBRARIES})
target_link_libraries(Client Qt5::Widgets)