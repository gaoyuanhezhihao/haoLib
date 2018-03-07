add_executable(config_unittest config_unittest.cpp)

find_package(Threads REQUIRED)
target_link_libraries(config_unittest config gtest gtest_main
    gmock gmock_main Threads::Threads)
add_test(NAME config_unittest COMMAND $<TARGET_FILE:config_unittest>)
