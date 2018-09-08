set(CMAKE_MINIMUM_VERSION 3.1)
cmake_minimum_required(VERSION ${CMAKE_MINIMUM_VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(InitHunter)
include(ucm)

project(SString)


hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

ucm_add_dirs(src TO SRC_LIST)
add_library(${PROJECT_NAME} ${SRC_LIST})

ucm_add_dirs(test TO TEST_LIST)
add_executable(${PROJECT_NAME}-test ${TEST_LIST})
target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} GTest::main) # GTest::gtest will be linked automatically
