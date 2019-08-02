include_guard()

find_package(Catch2 REQUIRED)
if(NOT Catch2_FOUND)
  message(FATAL_ERROR "Catch2 not found")
endif()

# Generate helpers for the tests
find_package(Python REQUIRED)
add_custom_target(
  gen_filepaths ALL
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  COMMAND ${Python_EXECUTABLE} gen_filepaths.py
  COMMENT
    "Running command: ${Python_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/gen_filepaths.py"
  )

# Helper function
function(setup_test test_target)
  include(Catch2Helpers)
  # NOTE: Assumes the source of the target has the same name as the target dot
  # cpp
  create_catch2_test(TARGET
                     ${test_target}
                     SOURCES
                     ${test_target}.cpp
                     INCLUDE
                     test_include
                     LINK_LIBRARIES
                     filetype_matcher)
  add_dependencies(${test_target} gen_filepaths)
  add_test(NAME ${test_target} COMMAND ${test_target})
endfunction()

# Unittests
setup_test(catch2_match)
setup_test(gtest_match)
setup_test(benchmark_match)
setup_test(unittest_match)
setup_test(pytest_match)

# Command line tests (relies on exit codes)
add_test(NAME show_help COMMAND $<TARGET_FILE:ftdetector> --help)
add_test(NAME ftdetector_single_file
         COMMAND $<TARGET_FILE:ftdetector>
                 --paths
                 ${CMAKE_SOURCE_DIR}/tests/testfiles/gtest/sample1_unittest.cc
                 --filetype
                 cpp)
add_test(
  NAME ftdetector_multiple_files
  COMMAND
    $<TARGET_FILE:ftdetector>
    --paths
    ${CMAKE_SOURCE_DIR}/tests/testfiles/gtest/sample1_unittest.cc,${CMAKE_SOURCE_DIR}/tests/testfiles/gtest/sample2_unittest.cc
    --filetype
    cpp)
add_test(NAME not_a_known_ft
         COMMAND $<TARGET_FILE:ftdetector>
                 --paths
                 ${CMAKE_SOURCE_DIR}/src/ftdetector.cpp
                 --filetype
                 cpp)
set_tests_properties(not_a_known_ft PROPERTIES WILL_FAIL TRUE)
