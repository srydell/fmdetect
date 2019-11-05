#include "Helpers/matcher_helpers.h"
#include "Matchers/Cpp/matchers.h"
#include "generated_filepaths.h"
#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("isBenchmark finds simple string versions of include",
          "[isBenchmark]") {
	using Matchers::Cpp::isBenchmark;
	REQUIRE(isBenchmark("#include <benchmark/benchmark.h>"));
	REQUIRE(isBenchmark("#include<benchmark/benchmark.h>"));
	REQUIRE(isBenchmark("#include\"benchmark/benchmark.h>"));
	REQUIRE(isBenchmark("#include<benchmark/benchmark.h\""));
	REQUIRE(isBenchmark("#include\"benchmark/benchmark.h\""));
	REQUIRE(isBenchmark("#include\"benchmark/benchmark.h\"     "));
	REQUIRE(isBenchmark("#include\"benchmark/benchmark.h\"	   "));
}

TEST_CASE("isBenchmark fails on simple string not matching correct include",
          "[isBenchmark]") {
	using Matchers::Cpp::isBenchmark;
	REQUIRE_FALSE(isBenchmark("#include <benchmark/benchmark.h >"));
	REQUIRE_FALSE(isBenchmark("#include<catch2/catch.h>"));
	REQUIRE_FALSE(isBenchmark("#include\"catch/catch.hpp>"));
	REQUIRE_FALSE(isBenchmark("#include\"something_else.hpp\""));
	REQUIRE_FALSE(isBenchmark("..fdashjkfhewuiqprhjksdalf"));
	REQUIRE_FALSE(isBenchmark("Jul 18, 2019"));
}

TEST_CASE("Run over test files", "[isBenchmark]") {
	using Matchers::Cpp::isBenchmark;

	std::string expected_ft = "benchmark";
	auto matchers = std::vector<Helpers::Matcher<decltype(isBenchmark)>>(
	    {Helpers::Matcher(expected_ft, isBenchmark)});

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
