add_library(tree_timer tree_timer.cc)
target_include_directories(tree_timer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_tree_timer test_tree_timer.cc)
target_link_libraries(test_tree_timer tree_timer)
