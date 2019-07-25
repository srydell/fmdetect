cmake_minimum_required(VERSION 3.14)

project(get_special_filetype VERSION 0.1 LANGUAGES CXX)

# Export compile flags to compile_commands.json database. Useful for linters and
# autocompletion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add custom scripts
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Define project_warnings and project_options targets
include(WarningsAndOptions)

include(SetupConan)
get_conan_helper()
# Require that conan is installed
conan_check(REQUIRED)
conan_setup_remotes()
# Install dependencies (defined in conanfile.{txt,py})
conan_cmake_run(CONANFILE
                conanfile.txt
                BASIC_SETUP
                CONAN_COMMAND
                ${CONAN_CMD}
                CMAKE_TARGETS
                BUILD
                missing)
# NOTE: Relies on cmake_paths generator
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_library(filetype_matcher src/filetype_matcher.cpp)
target_include_directories(filetype_matcher PRIVATE include)
target_link_libraries(filetype_matcher PRIVATE project_warnings project_options)
set_target_properties(filetype_matcher
                      PROPERTIES CXX_STANDARD_REQUIRED
                                 ON
                                 CXX_EXTENSIONS
                                 OFF)
target_link_libraries(filetype_matcher PRIVATE CONAN_PKG::CTRE)

add_executable(get_special_filetype src/get_special_filetype.cpp)
target_include_directories(get_special_filetype PRIVATE include)
target_link_libraries(get_special_filetype
                      PRIVATE project_warnings project_options)
set_target_properties(get_special_filetype
                      PROPERTIES CXX_STANDARD_REQUIRED
                                 ON
                                 CXX_EXTENSIONS
                                 OFF)
target_link_libraries(get_special_filetype
                      PRIVATE CONAN_PKG::CTRE CONAN_PKG::clara filetype_matcher)

option(BUILD_TESTING "Build the testing tree" ON)
if(BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  find_package(Catch2 REQUIRED)
  if(NOT Catch2_FOUND)
    message(FATAL_ERROR "Catch2 not found")
  endif()
  # enable_testing()

  # Generate helpers for the tests
  find_package(Python REQUIRED)
  add_custom_target(
    gen_filepaths ALL
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${Python_EXECUTABLE} test/gen_filepaths.py
    COMMENT
      "Running command: ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/gen_filepaths.py"
    )

  # Helper function
  function(setup_ctre_test ctre_test_target)
    target_link_libraries(${ctre_test_target}
                          PRIVATE project_options project_warnings
                                  CONAN_PKG::CTRE)
    target_include_directories(${ctre_test_target} PRIVATE include)

    add_dependencies(${ctre_test_target} gen_filepaths)
    target_include_directories(${ctre_test_target} PRIVATE test/test_include)
  endfunction()

  include(Catch2Helpers)
  create_catch2_test(TARGET
                     catch2_match
                     SOURCES
                     test/catch2_match.cpp)
  setup_ctre_test(catch2_match)

  create_catch2_test(TARGET
                     gtest_match
                     SOURCES
                     test/gtest_match.cpp)
  setup_ctre_test(gtest_match)

  create_catch2_test(TARGET
                     benchmark_match
                     SOURCES
                     test/benchmark_match.cpp)
  setup_ctre_test(benchmark_match)
endif()

option(BUILD_BENCHMARKS "Build the benchmarks" OFF)
if(BUILD_BENCHMARKS AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  # TODO: Add benchmarks
endif()
