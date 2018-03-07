find_package(Threads REQUIRED)

add_executable(config_unittest config_unittest.cpp)
target_link_libraries(config_unittest config gtest gtest_main
    gmock gmock_main Threads::Threads)
add_test(NAME config_unittest COMMAND $<TARGET_FILE:config_unittest>)

add_executable(traceable_get_test traceable_get_test.cpp )
target_link_libraries(traceable_get_test config)
