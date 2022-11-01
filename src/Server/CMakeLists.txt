FIND_PACKAGE(Boost 1.80 COMPONENTS REQUIRED)
set(SERVER_SRC
        ${PROJECT_SOURCE_DIR}/src/Server/Server.cpp
        ${PROJECT_SOURCE_DIR}/src/Server/core.cpp
        ${PROJECT_SOURCE_DIR}/src/Server/brocker/bid.cpp
        ${PROJECT_SOURCE_DIR}/src/Server/brocker/currency.cpp
        ${PROJECT_SOURCE_DIR}/src/Server/server/server.cpp
        ${PROJECT_SOURCE_DIR}/src/Server/server/session.cpp
        )

add_executable(Server ${SERVER_SRC})
target_link_libraries(Server ${Boost_LIBRARIES})