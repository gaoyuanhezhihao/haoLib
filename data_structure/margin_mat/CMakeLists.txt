add_library(margin_mat margin_mat.cpp margin_mat.hpp)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

target_include_directories(margin_mat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(test)
