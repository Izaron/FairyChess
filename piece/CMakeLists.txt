add_library(piece piece.cc board_piece.cc piece_registry.cc)

target_include_directories(piece INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS bit_storage)
target_link_libraries(piece PUBLIC ${LIBS})
