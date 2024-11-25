option(GENERATE_EXAMPLES "Examples generation" OFF)
if(GENERATE_EXAMPLES)
    list(APPEND VCPKG_MANIFEST_FEATURES "examples")
endif()

option(GENERATE_TESTS "Tests generation" OFF)
if(GENERATE_TESTS)
    list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

cmake_minimum_required (VERSION 3.25)
project(HTMCXX VERSION 0.1.0 LANGUAGES CXX)

include(cmake/setup.cmake)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(nameof CONFIG REQUIRED)

# HTMCXX build
add_library(htmcxx INTERFACE)
add_library(htmcxx::htmcxx ALIAS htmcxx)

target_include_directories(htmcxx INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(htmcxx INTERFACE nameof::nameof)

if(GENERATE_EXAMPLES)
    add_subdirectory(examples)
endif()

if(GENERATE_TESTS)
    add_subdirectory(test)
endif()

option(GENERATE_DOCS "Docs generation" OFF)
if(GENERATE_DOCS)
    add_subdirectory(docs)
endif()
