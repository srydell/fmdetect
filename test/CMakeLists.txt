include_guard()

find_package(Catch2 REQUIRED)
if(NOT Catch2_FOUND)
  message(FATAL_ERROR "Catch2 not found")
endif()
# enable_testing()

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
function(setup_ctre_test ctre_test_target)
  target_link_libraries(
    ${ctre_test_target}
    PRIVATE project_options project_warnings CONAN_PKG::CTRE)
  target_include_directories(${ctre_test_target}
                             PRIVATE ${CMAKE_SOURCE_DIR}/include)

  add_dependencies(${ctre_test_target} gen_filepaths)
  target_include_directories(${ctre_test_target} PRIVATE test_include)
endfunction()

include(Catch2Helpers)
create_catch2_test(TARGET
                   catch2_match
                   SOURCES
                   catch2_match.cpp
                   INCLUDE
                   ${CMAKE_SOURCE_DIR}/include
                   test_include
                   LINK_LIBRARIES
                   project_options
                   project_warnings
                   CONAN_PKG::CTRE)
add_dependencies(catch2_match gen_filepaths)

create_catch2_test(TARGET
                   gtest_match
                   SOURCES
                   gtest_match.cpp
                   INCLUDE
                   ${CMAKE_SOURCE_DIR}/include
                   test_include
                   LINK_LIBRARIES
                   project_options
                   project_warnings
                   CONAN_PKG::CTRE)
add_dependencies(gtest_match gen_filepaths)

create_catch2_test(TARGET
                   benchmark_match
                   SOURCES
                   benchmark_match.cpp
                   INCLUDE
                   ${CMAKE_SOURCE_DIR}/include
                   test_include
                   LINK_LIBRARIES
                   project_options
                   project_warnings
                   CONAN_PKG::CTRE)
add_dependencies(benchmark_match gen_filepaths)

create_catch2_test(TARGET
                   unittest_match
                   SOURCES
                   unittest_match.cpp
                   INCLUDE
                   ${CMAKE_SOURCE_DIR}/include
                   test_include
                   LINK_LIBRARIES
                   project_options
                   project_warnings
                   CONAN_PKG::CTRE)
add_dependencies(unittest_match gen_filepaths)
