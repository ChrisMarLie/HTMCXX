find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tag_test tag_test.cc)
target_link_libraries(tag_test PRIVATE htmcxx::htmcxx GTest::gtest_main)

gtest_discover_tests(tag_test)