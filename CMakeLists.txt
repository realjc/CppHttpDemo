cmake_minimum_required(VERSION 2.8)
project(web LANGUAGES C CXX)

add_definitions(-std=c++11)
add_definitions(-w)

include_directories(
    "${PROJECT_SOURCE_DIR}/server"
    "${PROJECT_SOURCE_DIR}/mongoose"
    "${PROJECT_SOURCE_DIR}/client"
)

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(mongoose)

add_executable(test_http_server "test_http_server.cpp")
target_link_libraries(test_http_server  server )
target_link_libraries(test_http_server  mongoose )
add_executable(test_http_client "test_http_client.cpp")
target_link_libraries(test_http_client  client )
target_link_libraries(test_http_client  mongoose )