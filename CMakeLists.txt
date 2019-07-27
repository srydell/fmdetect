cmake_minimum_required(VERSION 3.14)

project(ftdetect VERSION 0.1 LANGUAGES CXX)

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
include(TargetHelpers)

create_target(TARGET
              filetype_matcher
              IS_LIBRARY
              SOURCES
              src/filetype_matcher.cpp
              INCLUDE
              include
              LINK_LIBRARIES
              project_warnings
              project_options
              CONAN_PKG::CTRE)

create_target(TARGET
              ftdetect
              SOURCES
              src/ftdetect.cpp
              INCLUDE
              include
              LINK_LIBRARIES
              project_warnings
              project_options
              CONAN_PKG::clara
              CONAN_PKG::CTRE
              filetype_matcher)

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
                     test/catch2_match.cpp
                     INCLUDE
                     include
                     test/test_include
                     LINK_LIBRARIES
                     project_options
                     project_warnings
                     CONAN_PKG::CTRE)
  add_dependencies(catch2_match gen_filepaths)

  create_catch2_test(TARGET
                     gtest_match
                     SOURCES
                     test/gtest_match.cpp
                     INCLUDE
                     include
                     test/test_include
                     LINK_LIBRARIES
                     project_options
                     project_warnings
                     CONAN_PKG::CTRE)
  add_dependencies(gtest_match gen_filepaths)

  create_catch2_test(TARGET
                     benchmark_match
                     SOURCES
                     test/benchmark_match.cpp
                     INCLUDE
                     include
                     test/test_include
                     LINK_LIBRARIES
                     project_options
                     project_warnings
                     CONAN_PKG::CTRE)
  add_dependencies(benchmark_match gen_filepaths)
endif()

option(BUILD_BENCHMARKS "Build the benchmarks" OFF)
if(BUILD_BENCHMARKS AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  # TODO: Add benchmarks
endif()
