#include "Helpers/matcher_helpers.h"
#include "Matchers/Python/matchers.h"
#include "generated_filepaths.h"
#include <catch2/catch.hpp>

TEST_CASE("isPytest finds simple string versions of import statements",
          "[isPytest]") {
	using Matchers::Python::isPytest;
	REQUIRE(isPytest("import pytest"));
	REQUIRE(isPytest("import pytest as something_else"));
	REQUIRE(isPytest("from pytest import stuff"));
	REQUIRE(isPytest("from pytest import hfjdklasioeruwq"));
}

TEST_CASE("isPytest fails on simple string not matching correct include",
          "[isPytest]") {
	using Matchers::Python::isPytest;
	REQUIRE_FALSE(isPytest("import numpy"));
	REQUIRE_FALSE(isPytest("import pytestos"));
	REQUIRE_FALSE(isPytest("import pytestos as something_else"));
	REQUIRE_FALSE(isPytest("from unittestis import stuff"));
	REQUIRE_FALSE(isPytest("#include <catch2/catch.hpp >"));
	REQUIRE_FALSE(isPytest("#include<catch2/catch.h>"));
	REQUIRE_FALSE(isPytest("#include\"catch/catch.hpp>"));
	REQUIRE_FALSE(isPytest("#include\"something_else.hpp\""));
	REQUIRE_FALSE(isPytest("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(isPytest("Jul 18, 2019"));
}

TEST_CASE("Run over test files", "[isPytest]") {
	using Helpers::Matcher;
	using Matchers::Python::isPytest;

	std::string expected_ft = "pytest";
	auto matchers = std::vector<Matcher<decltype(isPytest)>>(
	    {Matcher(expected_ft, isPytest)});

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
