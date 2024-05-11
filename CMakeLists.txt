cmake_minimum_required (VERSION 3.25)
project(htmcxx VERSION 0.1.0 LANGUAGES CXX)

include(cmake/setup.cmake)

find_package(nameof CONFIG REQUIRED)

# HTMCXX build
add_library(htmcxx INTERFACE)
add_library(htmcxx::htmcxx ALIAS htmcxx)

target_include_directories(htmcxx INTERFACE include)
target_link_libraries(htmcxx INTERFACE nameof::nameof)

add_subdirectory(examples)
add_subdirectory(test)
