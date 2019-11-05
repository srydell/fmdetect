#include "Helpers/matcher_helpers.h"
#include "Matchers/Cpp/matchers.h"
#include "generated_filepaths.h"
#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("isCatch2 finds simple string versions of include", "[isCatch2]") {
	using Matchers::Cpp::isCatch2;
	REQUIRE(isCatch2("#include <catch2/catch.hpp>"));
	REQUIRE(isCatch2("#include<catch2/catch.hpp>"));
	REQUIRE(isCatch2("#include\"catch2/catch.hpp>"));
	REQUIRE(isCatch2("#include<catch2/catch.hpp\""));
	REQUIRE(isCatch2("#include\"catch2/catch.hpp\""));
	REQUIRE(isCatch2("#include\"catch2/catch.hpp\"     "));
	REQUIRE(isCatch2("#include\"catch2/catch.hpp\"	   "));
}

TEST_CASE("isCatch2 fails on simple string not matching correct include",
          "[isCatch2]") {
	using Matchers::Cpp::isCatch2;
	// Added space
	REQUIRE_FALSE(isCatch2("#include <catch2/catch.hpp >"));
	// Missing hpp
	REQUIRE_FALSE(isCatch2("#include<catch2/catch.h>"));
	// Missing 2
	REQUIRE_FALSE(isCatch2("#include\"catch/catch.hpp>"));
	// Not catch2
	REQUIRE_FALSE(isCatch2("#include\"something_else.hpp\""));
	// 'Random' letters
	REQUIRE_FALSE(isCatch2("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(isCatch2("Jul 18, 2019"));
}

TEST_CASE("Run over test files", "[isCatch2]") {
	using Helpers::Matcher;
	using Matchers::Cpp::isCatch2;
	std::string expected_ft = "catch2";
	auto s = std::vector<Matcher<decltype(isCatch2)>>(
	    {Matcher(expected_ft, isCatch2)});

	// Catch2 files
	for (auto &filename : testfiles::catch2) {
		REQUIRE(parseFile(filename, s) == expected_ft);
	}

	// Gtest files
	for (auto &filename : testfiles::gtest) {
		REQUIRE_FALSE(parseFile(filename, s) == expected_ft);
	}
}
