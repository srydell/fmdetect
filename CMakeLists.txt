cmake_minimum_required(VERSION 3.14)

project(special_filetypes VERSION 0.1 LANGUAGES CXX)

# Export compile flags to compile_commands.json database. Useful for linters and
# autocompletion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# If no build type is provided explicitly, set it to Release
if(NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  endif()
endif()

# Add custom scripts
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Define project_warnings and project_options targets
include(WarningsAndOptions)

include(SetupConan)
get_conan_helper()
# Require that conan is installed
conan_check(REQUIRED)
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

add_executable(get_special_filetype
               src/get_special_filetype.cpp
               include/filetypeMatcher.h
               include/get_special_filetype.h
               include/matchers.h)
target_include_directories(get_special_filetype PRIVATE include)
target_link_libraries(get_special_filetype
                      PRIVATE project_warnings project_options)
set_target_properties(get_special_filetype
                      PROPERTIES CXX_STANDARD_REQUIRED
                                 ON
                                 CXX_EXTENSIONS
                                 OFF)
target_link_libraries(get_special_filetype PRIVATE CONAN_PKG::CTRE)

option(BUILD_TESTING "Build the testing tree" ON)
if(BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  find_package(Catch2 REQUIRED)
  if(NOT Catch2_FOUND)
    message(FATAL_ERROR "Catch2 not found")
  endif()
  # enable_testing()

  # Helper function
  function(setup_ctre_test ctre_test_target)
    target_link_libraries(${ctre_test_target}
                          PRIVATE project_options project_warnings
                                  CONAN_PKG::CTRE)
    target_include_directories(${ctre_test_target} PRIVATE include)
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
