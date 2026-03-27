include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_test test_main.cpp)

target_link_libraries(unit_test PUBLIC ImGui-SFML::ImGui-SFML GTest::gtest_main)

add_test(NAME TEST COMMAND unit_test)