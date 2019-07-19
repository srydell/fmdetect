#include "get_special_filetype.h"
#include "matchers.h"
#include <catch2/catch.hpp>

TEST_CASE("isGtest finds simple string versions of include", "[isGtest]") {
	REQUIRE(cpp::matchers::isGtest("#include <gtest/gtest.h>"));
	REQUIRE(cpp::matchers::isGtest("#include<gtest/gtest.h>"));
	REQUIRE(cpp::matchers::isGtest("#include\"gtest/gtest.h>"));
	REQUIRE(cpp::matchers::isGtest("#include<gtest/gtest.h\""));
	REQUIRE(cpp::matchers::isGtest("#include\"gtest/gtest.h\""));
	REQUIRE(cpp::matchers::isGtest("#include\"gtest/gtest.h\"     "));
	REQUIRE(cpp::matchers::isGtest("#include\"gtest/gtest.h\"	   "));
}

TEST_CASE("isGtest fails on simple string not matching correct include",
          "[isGtest]") {
	// Added space
	REQUIRE_FALSE(cpp::matchers::isGtest("#include <gtest/gtest.h >"));
	// .h -> .hpp
	REQUIRE_FALSE(cpp::matchers::isGtest("#include<gtest/gtest.hpp>"));
	// Not gtest
	REQUIRE_FALSE(cpp::matchers::isGtest("#include\"something_else.h\""));
	// 'Random' letters
	REQUIRE_FALSE(cpp::matchers::isGtest("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(cpp::matchers::isGtest("Jul 18, 2019"));
}
