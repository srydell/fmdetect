#include "filetypeMatcher.h"
#include "generated_filepaths.h"
#include "get_special_filetype.h"
#include "matchers.h"
#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("isBenchmark finds simple string versions of include",
          "[isBenchmark]") {
	REQUIRE(cpp::isBenchmark("#include <benchmark/benchmark.h>"));
	REQUIRE(cpp::isBenchmark("#include<benchmark/benchmark.h>"));
	REQUIRE(cpp::isBenchmark("#include\"benchmark/benchmark.h>"));
	REQUIRE(cpp::isBenchmark("#include<benchmark/benchmark.h\""));
	REQUIRE(cpp::isBenchmark("#include\"benchmark/benchmark.h\""));
	REQUIRE(cpp::isBenchmark("#include\"benchmark/benchmark.h\"     "));
	REQUIRE(cpp::isBenchmark("#include\"benchmark/benchmark.h\"	   "));
}

TEST_CASE("isBenchmark fails on simple string not matching correct include",
          "[isBenchmark]") {
	REQUIRE_FALSE(cpp::isBenchmark("#include <benchmark/benchmark.h >"));
	REQUIRE_FALSE(cpp::isBenchmark("#include<catch2/catch.h>"));
	REQUIRE_FALSE(cpp::isBenchmark("#include\"catch/catch.hpp>"));
	REQUIRE_FALSE(cpp::isBenchmark("#include\"something_else.hpp\""));
	REQUIRE_FALSE(cpp::isBenchmark("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(cpp::isBenchmark("Jul 18, 2019"));
}

TEST_CASE("Run over test files", "[isBenchmark]") {
	std::string expected_ft = "benchmark";
	auto matchers = std::vector<FiletypeMatcher>(
	    {FiletypeMatcher(expected_ft, cpp::isBenchmark)});

	// Benchmark files
	for (auto &filename : testfiles::benchmark) {
		REQUIRE(parseFile(filename, matchers) == expected_ft);
	}

	// Catch2 files
	for (auto &filename : testfiles::catch2) {
		REQUIRE_FALSE(parseFile(filename, matchers) == expected_ft);
	}

	// Gtest files
	for (auto &filename : testfiles::gtest) {
		REQUIRE_FALSE(parseFile(filename, matchers) == expected_ft);
	}
}
