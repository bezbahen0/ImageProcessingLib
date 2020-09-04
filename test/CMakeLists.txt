cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")
set(PROJECT_UNIT_TESTS_NAME ${PROJECT_NAME_STR}_unit_tests)

find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)

file(GLOB UNIT_TEST_HEADERS ${PROJECT_SOURCE_DIR}/test/*.hpp)
file(GLOB UNIT_TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp)

set(UNIT_TEST_INCLUDES ${PROJECT_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR}) 

include_directories(${Boost_INCLUDE_DIR})
include_directories(${UNIT_TEST_INCLUDES})

if(Boost_FOUND)
    add_definitions(-DBOOST_TEST_DYN_LINK)
    add_executable(${PROJECT_UNIT_TESTS_NAME} ${UNIT_TEST_HEADERS} ${UNIT_TEST_SOURCES})
    target_link_libraries(${PROJECT_UNIT_TESTS_NAME} ${Boost_LIBRARIES})

    enable_testing()
    add_test(DemoTest ${PROJECT_UNIT_TESTS_NAME})
else()
    message("boost not found, pleas install boost libreris for compilation unit_test")
endif()


