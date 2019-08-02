cmake_minimum_required(VERSION 3.14)

project(ftdetector VERSION 0.1 LANGUAGES CXX)

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
              ftdetector
              SOURCES
              src/ftdetector.cpp
              LINK_LIBRARIES
              CONAN_PKG::clara
              filetype_matcher)

option(BUILD_TESTING "Build the testing tree" ON)
if(BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  enable_testing()
  add_subdirectory(tests)
endif()

option(BUILD_BENCHMARKS "Build the benchmarks" OFF)
if(BUILD_BENCHMARKS AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  # TODO: Add benchmarks
endif()
