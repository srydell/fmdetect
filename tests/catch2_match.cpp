#include "generated_filepaths.h"
#include "matcher_helpers.h"
#include "matchers.h"
#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("isCatch2 finds simple string versions of include", "[isCatch2]") {
	REQUIRE(cpp::isCatch2("#include <catch2/catch.hpp>"));
	REQUIRE(cpp::isCatch2("#include<catch2/catch.hpp>"));
	REQUIRE(cpp::isCatch2("#include\"catch2/catch.hpp>"));
	REQUIRE(cpp::isCatch2("#include<catch2/catch.hpp\""));
	REQUIRE(cpp::isCatch2("#include\"catch2/catch.hpp\""));
	REQUIRE(cpp::isCatch2("#include\"catch2/catch.hpp\"     "));
	REQUIRE(cpp::isCatch2("#include\"catch2/catch.hpp\"	   "));
}

TEST_CASE("isCatch2 fails on simple string not matching correct include",
          "[isCatch2]") {
	// Added space
	REQUIRE_FALSE(cpp::isCatch2("#include <catch2/catch.hpp >"));
	// Missing hpp
	REQUIRE_FALSE(cpp::isCatch2("#include<catch2/catch.h>"));
	// Missing 2
	REQUIRE_FALSE(cpp::isCatch2("#include\"catch/catch.hpp>"));
	// Not catch2
	REQUIRE_FALSE(cpp::isCatch2("#include\"something_else.hpp\""));
	// 'Random' letters
	REQUIRE_FALSE(cpp::isCatch2("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(cpp::isCatch2("Jul 18, 2019"));
}

TEST_CASE("Run over test files", "[isCatch2]") {
	using Helpers::Matcher;
	std::string expected_ft = "catch2";
	auto s = std::vector<Matcher>({Matcher(expected_ft, cpp::isCatch2)});

	// Catch2 files
	for (auto &filename : testfiles::catch2) {
		REQUIRE(parseFile(filename, s) == expected_ft);
	}

	// Gtest files
	for (auto &filename : testfiles::gtest) {
		REQUIRE_FALSE(parseFile(filename, s) == expected_ft);
	}
}
