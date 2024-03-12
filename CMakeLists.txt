cmake_minimum_required (VERSION 3.25)
project(htmcxx)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(cmake/generate.cmake)

generate_tags_file()
generate_attributes_file()

add_library(htmcxx INTERFACE)
add_library(htmcxx::htmcxx ALIAS htmcxx)

target_include_directories(htmcxx INTERFACE include)

add_subdirectory(examples)
