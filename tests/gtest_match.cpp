#include "Helpers/matcher_helpers.h"
#include "generated_filepaths.h"
#include "matchers.h"
#include <catch2/catch.hpp>

TEST_CASE("isGtest finds simple string versions of include", "[isGtest]") {
	REQUIRE(cpp::isGtest("#include <gtest/gtest.h>"));
	REQUIRE(cpp::isGtest("#include<gtest/gtest.h>"));
	REQUIRE(cpp::isGtest("#include\"gtest/gtest.h>"));
	REQUIRE(cpp::isGtest("#include<gtest/gtest.h\""));
	REQUIRE(cpp::isGtest("#include\"gtest/gtest.h\""));
	REQUIRE(cpp::isGtest("#include\"gtest/gtest.h\"     "));
	REQUIRE(cpp::isGtest("#include\"gtest/gtest.h\"	   "));
}

TEST_CASE("isGtest fails on simple string not matching correct include",
          "[isGtest]") {
	// Added space
	REQUIRE_FALSE(cpp::isGtest("#include <gtest/gtest.h >"));
	// .h -> .hpp
	REQUIRE_FALSE(cpp::isGtest("#include<gtest/gtest.hpp>"));
	// Not gtest
	REQUIRE_FALSE(cpp::isGtest("#include\"something_else.h\""));
	// 'Random' letters
	REQUIRE_FALSE(cpp::isGtest("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(cpp::isGtest("Jul 18, 2019"));
}

TEST_CASE("Run over test files", "[isGtest]") {
	std::string expected_ft = "gtest";
	auto s = std::vector<Helpers::Matcher>(
	    {Helpers::Matcher(expected_ft, cpp::isGtest)});

	// Gtest files
	for (auto &filename : testfiles::gtest) {
		REQUIRE(parseFile(filename, s) == expected_ft);
	}

	// Catch2 files
	for (auto &filename : testfiles::catch2) {
		REQUIRE_FALSE(parseFile(filename, s) == expected_ft);
	}
}
