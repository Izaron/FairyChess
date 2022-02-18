add_library(vanilla_figures pawn.cc)

target_include_directories(vanilla_figures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS figure)
target_link_libraries(vanilla_figures PUBLIC ${LIBS})
