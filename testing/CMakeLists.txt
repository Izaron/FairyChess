add_library(testing testing.cc)

target_include_directories(testing INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS gtest_main pretty_printer)
target_link_libraries(testing PUBLIC ${LIBS})
