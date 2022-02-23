add_library(pretty_printer pretty_printer.cc)

target_include_directories(pretty_printer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS board)
target_link_libraries(pretty_printer PUBLIC ${LIBS})
