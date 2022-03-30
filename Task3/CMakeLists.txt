cmake_minimum_required(VERSION 3.0.0)
project(Task3 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Task3 src/main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
