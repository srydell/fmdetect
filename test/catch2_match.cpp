#include "filetypeMatcher.h"
#include "generated_filepaths.h"
#include "get_special_filetype.h"
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

TEST_CASE("Run over Catch2 test files", "[isCatch2]") {
	std::string expected_ft = "catch2";
	auto s = std::vector<FiletypeMatcher>(
	    {FiletypeMatcher(expected_ft, cpp::isCatch2)});

	for (auto &filename : testfiles::catch2) {
		REQUIRE(parseFile(filename, s) == expected_ft);
	}
}
