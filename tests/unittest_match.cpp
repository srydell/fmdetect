#include "Helpers/matcher_helpers.h"
#include "Matchers/Python/matchers.h"
#include "generated_filepaths.h"
#include <catch2/catch.hpp>

TEST_CASE("isUnittest finds simple string versions of import statements",
          "[isUnittest]") {
	using Matchers::Python::isUnittest;
	REQUIRE(isUnittest("import unittest"));
	REQUIRE(isUnittest("import unittest as something_else"));
	REQUIRE(isUnittest("from unittest import stuff"));
	REQUIRE(isUnittest("from unittest import stuff"));
}

TEST_CASE("isUnittest fails on simple string not matching correct include",
          "[isUnittest]") {
	using Matchers::Python::isUnittest;
	REQUIRE_FALSE(isUnittest("import numpy"));
	REQUIRE_FALSE(isUnittest("import unittestos"));
	REQUIRE_FALSE(isUnittest("import unittestos as something_else"));
	REQUIRE_FALSE(isUnittest("from unittestis import stuff"));
	REQUIRE_FALSE(isUnittest("#include <catch2/catch.hpp >"));
	REQUIRE_FALSE(isUnittest("#include<catch2/catch.h>"));
	REQUIRE_FALSE(isUnittest("#include\"catch/catch.hpp>"));
	REQUIRE_FALSE(isUnittest("#include\"something_else.hpp\""));
	REQUIRE_FALSE(isUnittest("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(isUnittest("Jul 18, 2019"));
}

TEST_CASE("Run over test files", "[isUnittest]") {
	using Helpers::Matcher;
	using Matchers::Python::isUnittest;
	std::string expected_ft = "unittest";
	auto matchers = std::vector<Matcher<decltype(isUnittest)>>(
	    {Matcher(expected_ft, isUnittest)});

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
