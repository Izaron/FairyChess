add_library(move_generator move_generator.cc)

target_include_directories(move_generator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS board)
target_link_libraries(move_generator PUBLIC ${LIBS})
