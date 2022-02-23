add_library(
    graphics
    graphics.cc
)

target_include_directories(graphics INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS board piece)
target_link_libraries(graphics PUBLIC ${LIBS})
