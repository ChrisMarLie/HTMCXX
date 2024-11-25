add_executable(hello_world hello_world.cc)
target_link_libraries(hello_world PRIVATE htmcxx::htmcxx)
target_compile_options(hello_world INTERFACE ${SANITIZERS} ${WARNINGS})
target_link_options(hello_world INTERFACE ${SANITIZERS} ${WARNINGS})

add_executable(dynamic_building dynamic_building.cc)
target_link_libraries(dynamic_building PRIVATE htmcxx::htmcxx)
target_compile_options(dynamic_building INTERFACE ${SANITIZERS} ${WARNINGS})
target_link_options(dynamic_building INTERFACE ${SANITIZERS} ${WARNINGS})

find_package(Crow)
add_executable(server_htmcxx server_htmcxx.cc)
target_link_libraries(server_htmcxx PRIVATE Crow::Crow htmcxx::htmcxx)