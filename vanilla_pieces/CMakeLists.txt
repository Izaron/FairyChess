add_library(vanilla_pieces pawn.cc)

target_include_directories(vanilla_pieces INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS piece)
target_link_libraries(vanilla_pieces PUBLIC ${LIBS})
