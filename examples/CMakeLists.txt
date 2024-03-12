add_executable(hello_world hello_world.cc)
target_link_libraries(hello_world PRIVATE htmcxx::htmcxx)

add_executable(dynamic_building dynamic_building.cc)
target_link_libraries(dynamic_building PRIVATE htmcxx::htmcxx)