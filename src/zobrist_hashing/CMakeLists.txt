add_library(zobrist_hashing zobrist_hashing.cc)

target_include_directories(zobrist_hashing INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS board)
target_link_libraries(zobrist_hashing PUBLIC ${LIBS})
