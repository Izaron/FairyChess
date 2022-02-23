add_library(bit_storage bit_storage.cc)

target_include_directories(bit_storage INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

add_executable(
    bit_storage_test
    bit_storage_ut.cc
)

target_link_libraries(
    bit_storage_test
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(bit_storage_test)
