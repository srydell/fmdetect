#pragma once

#include "Helpers/matcher_helpers.h"
#include "ctre.hpp"
#include <array>
#include <string_view>

namespace Matchers::Cpp {
namespace {
static constexpr auto catch2_pattern =
    ctll::fixed_string{"#include ?(<|\")(catch2/)?catch.hpp(>|\")\\s*?"};

static constexpr auto gtest_pattern =
    ctll::fixed_string{"#include ?(<|\")(gtest/)?gtest.h(>|\")\\s*?"};

static constexpr auto benchmark_pattern =
    ctll::fixed_string{"#include ?(<|\")(benchmark/)?benchmark.h(>|\")\\s*?"};
}    // namespace

constexpr bool isCatch2(std::string_view sv) noexcept {
	return ctre::match<catch2_pattern>(sv);
}

constexpr bool isGtest(std::string_view sv) noexcept {
	return ctre::match<gtest_pattern>(sv);
}

constexpr bool isBenchmark(std::string_view sv) noexcept {
	return ctre::match<benchmark_pattern>(sv);
}

auto getMatchers() noexcept {
	using Helpers::Matcher;
	return std::array<Matcher<decltype(isCatch2)>, 3>(
	    {Matcher("catch2", isCatch2),
	     Matcher("gtest", isGtest),
	     Matcher("benchmark", isBenchmark)});
}
}    // namespace Matchers::Cpp
