find_package(Threads REQUIRED)

add_executable(fileutils_unittest fileutils_unittest.cpp)
target_link_libraries(fileutils_unittest fileutils gtest gtest_main
    gmock gmock_main Threads::Threads)
add_test(NAME fileutils_unittest COMMAND $<TARGET_FILE:fileutils_unittest>)
