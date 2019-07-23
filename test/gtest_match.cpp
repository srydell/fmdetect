#include "get_special_filetype.h"
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
