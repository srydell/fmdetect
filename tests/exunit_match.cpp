#include "Helpers/matcher_helpers.h"
#include "Matchers/Elixir/matchers.h"
#include "generated_filepaths.h"
#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("isExUnit finds simple string versions of use ExUnit", "[isCatch2]") {
	using Matchers::Elixir::isExUnit;
	REQUIRE(isExUnit("use ExUnit.Case, async: true"));
	REQUIRE(isExUnit("use ExUnit.Case"));
	REQUIRE(isExUnit("       use ExUnit.Case, async: true"));
	REQUIRE(isExUnit("\t      use ExUnit.Case, async: true   "));
}

TEST_CASE("isExUnit fails on simple string not matching correct include",
          "[isExUnit]") {
	using Matchers::Elixir::isExUnit;
	// Extra word before
	REQUIRE_FALSE(isExUnit("do use ExUnit.Case, async: true"));
	// Spelling
	REQUIRE_FALSE(isExUnit("uze ExUnit.Case"));
	// Comma instead of dot
	REQUIRE_FALSE(isExUnit("       use ExUnit,Case, async: true"));
	REQUIRE_FALSE(isExUnit("whtnseriao ExUnit.Case"));
	// No use
	REQUIRE_FALSE(isExUnit("ExUnit.Case"));
	// 'Random' letters
	REQUIRE_FALSE(isExUnit("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(isExUnit("Jul 18, 2019"));
	// Must uso something
	REQUIRE_FALSE(isExUnit("use Exunit"));
}

TEST_CASE("Run over test files", "[isExUnit]") {
	std::string expected_ft = "exunit";
	auto matcher = Matchers::Elixir::getMatchers();

	// exunit files
	for (auto& filename : testfiles::exunit) {
		REQUIRE(parseFile(filename, matcher) == expected_ft);
	}

	// Catch2 files
	for (auto &filename : testfiles::catch2) {
		REQUIRE_FALSE(parseFile(filename, matcher) == expected_ft);
	}

	// Catch2 files
	for (auto& filename : testfiles::catch2) {
		REQUIRE_FALSE(parseFile(filename, matcher) == expected_ft);
	}

	// Gtest files
	for (auto &filename : testfiles::gtest) {
		REQUIRE_FALSE(parseFile(filename, matcher) == expected_ft);
	}
}
