cmake_minimum_required(VERSION 3.10)
project(BigGameServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)


link_directories(/usr/lib/x86_64-linux-gnu)

add_executable(BigGameServer ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/webserver/Webserver.cpp
    ${CMAKE_SOURCE_DIR}/src/webserver/RestEndpointController.cpp
    ${CMAKE_SOURCE_DIR}/src/game/GetKeyEndpoint.cpp
    ${CMAKE_SOURCE_DIR}/src/game/AuthRestEndpoint.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/SqlQueryExecutor.cpp
) 
target_link_libraries(BigGameServer mariadbcpp.so)