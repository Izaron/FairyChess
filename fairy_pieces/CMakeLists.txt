add_library(
    fairy_pieces
    dummy.cc
)

target_include_directories(fairy_pieces INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS piece)
target_link_libraries(fairy_pieces PUBLIC ${LIBS})
