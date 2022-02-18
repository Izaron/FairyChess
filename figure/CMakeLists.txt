add_library(figure figure.cc board_figure.cc)

target_include_directories(figure INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS bit_storage)
target_link_libraries(figure PUBLIC ${LIBS})
