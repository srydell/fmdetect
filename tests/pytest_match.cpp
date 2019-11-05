#include "Helpers/matcher_helpers.h"
#include "generated_filepaths.h"
#include "matchers.h"
#include <catch2/catch.hpp>

TEST_CASE("isPytest finds simple string versions of import statements",
          "[isPytest]") {
	REQUIRE(python::isPytest("import pytest"));
	REQUIRE(python::isPytest("import pytest as something_else"));
	REQUIRE(python::isPytest("from pytest import stuff"));
	REQUIRE(python::isPytest("from pytest import hfjdklasioeruwq"));
}

TEST_CASE("isPytest fails on simple string not matching correct include",
          "[isPytest]") {
	REQUIRE_FALSE(python::isPytest("import numpy"));
	REQUIRE_FALSE(python::isPytest("import pytestos"));
	REQUIRE_FALSE(python::isPytest("import pytestos as something_else"));
	REQUIRE_FALSE(python::isPytest("from unittestis import stuff"));
	REQUIRE_FALSE(python::isPytest("#include <catch2/catch.hpp >"));
	REQUIRE_FALSE(python::isPytest("#include<catch2/catch.h>"));
	REQUIRE_FALSE(python::isPytest("#include\"catch/catch.hpp>"));
	REQUIRE_FALSE(python::isPytest("#include\"something_else.hpp\""));
	REQUIRE_FALSE(python::isPytest("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(python::isPytest("Jul 18, 2019"));
}

TEST_CASE("Run over test files", "[isPytest]") {
	using Helpers::Matcher;
	std::string expected_ft = "pytest";
	auto matchers =
	    std::vector<Matcher>({Matcher(expected_ft, python::isPytest)});

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
