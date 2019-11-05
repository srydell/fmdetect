#include "Helpers/matcher_helpers.h"
#include "generated_filepaths.h"
#include "matchers.h"
#include <catch2/catch.hpp>

TEST_CASE("isUnittest finds simple string versions of import statements",
          "[isUnittest]") {
	REQUIRE(python::isUnittest("import unittest"));
	REQUIRE(python::isUnittest("import unittest as something_else"));
	REQUIRE(python::isUnittest("from unittest import stuff"));
	REQUIRE(python::isUnittest("from unittest import stuff"));
}

TEST_CASE("isUnittest fails on simple string not matching correct include",
          "[isUnittest]") {
	REQUIRE_FALSE(python::isUnittest("import numpy"));
	REQUIRE_FALSE(python::isUnittest("import unittestos"));
	REQUIRE_FALSE(python::isUnittest("import unittestos as something_else"));
	REQUIRE_FALSE(python::isUnittest("from unittestis import stuff"));
	REQUIRE_FALSE(python::isUnittest("#include <catch2/catch.hpp >"));
	REQUIRE_FALSE(python::isUnittest("#include<catch2/catch.h>"));
	REQUIRE_FALSE(python::isUnittest("#include\"catch/catch.hpp>"));
	REQUIRE_FALSE(python::isUnittest("#include\"something_else.hpp\""));
	REQUIRE_FALSE(python::isUnittest("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(python::isUnittest("Jul 18, 2019"));
}

TEST_CASE("Run over test files", "[isUnittest]") {
	using Helpers::Matcher;
	std::string expected_ft = "unittest";
	auto matchers = std::vector<Matcher<decltype(cpp::isCatch2)>>(
	    {Matcher(expected_ft, python::isUnittest)});

	// Catch2 files
	for (auto &filename : testfiles::catch2) {
		REQUIRE_FALSE(parseFile(filename, matchers) == expected_ft);
	}

	// Gtest files
	for (auto &filename : testfiles::gtest) {
		REQUIRE_FALSE(parseFile(filename, matchers) == expected_ft);
	}

	// Benchmark files
	for (auto &filename : testfiles::benchmark) {
		REQUIRE_FALSE(parseFile(filename, matchers) == expected_ft);
	}
}
