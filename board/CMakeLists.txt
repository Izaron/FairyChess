add_library(board board.cc)

target_include_directories(board INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
