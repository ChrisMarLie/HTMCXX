find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(basic_test basic_test.cc)
target_link_libraries(basic_test PRIVATE htmcxx::htmcxx  GTest::gtest_main)

gtest_discover_tests(basic_test)