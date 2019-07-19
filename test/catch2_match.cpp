#include "get_special_filetype.h"
#include "matchers.h"
#include <catch2/catch.hpp>

TEST_CASE("isCatch2 finds simple string versions of include", "[isCatch2]") {
	REQUIRE(cpp::matchers::isCatch2("#include <catch2/catch.hpp>"));
	REQUIRE(cpp::matchers::isCatch2("#include<catch2/catch.hpp>"));
	REQUIRE(cpp::matchers::isCatch2("#include\"catch2/catch.hpp>"));
	REQUIRE(cpp::matchers::isCatch2("#include<catch2/catch.hpp\""));
	REQUIRE(cpp::matchers::isCatch2("#include\"catch2/catch.hpp\""));
	REQUIRE(cpp::matchers::isCatch2("#include\"catch2/catch.hpp\"     "));
	REQUIRE(cpp::matchers::isCatch2("#include\"catch2/catch.hpp\"	   "));
}

TEST_CASE("isCatch2 fails on simple string not matching correct include",
          "[isCatch2]") {
	// Added space
	REQUIRE_FALSE(cpp::matchers::isCatch2("#include <catch2/catch.hpp >"));
	// Missing hpp
	REQUIRE_FALSE(cpp::matchers::isCatch2("#include<catch2/catch.h>"));
	// Missing 2
	REQUIRE_FALSE(cpp::matchers::isCatch2("#include\"catch/catch.hpp>"));
	// Not catch2
	REQUIRE_FALSE(cpp::matchers::isCatch2("#include\"something_else.hpp\""));
	// 'Random' letters
	REQUIRE_FALSE(cpp::matchers::isCatch2("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(cpp::matchers::isCatch2("Jul 18, 2019"));
}
