find_package(GTest REQUIRED)

add_executable(unit_test test_main.cpp)

target_link_libraries(unit_test PUBLIC ImGui-SFML::ImGui-SFML GTest::gtest_main)

add_test(NAME TEST COMMAND unit_test)