#pragma once

#include "ctre.hpp"
#include <string_view>

namespace cpp {
namespace patterns {
static constexpr auto catch2_pattern =
    ctll::fixed_string{"#include ?(<|\")(catch2/)?catch.hpp(>|\")\\s*?"};

static constexpr auto gtest_pattern =
    ctll::fixed_string{"#include ?(<|\")(gtest/)?gtest.h(>|\")\\s*?"};

static constexpr auto benchmark_pattern =
    ctll::fixed_string{"#include ?(<|\")(benchmark/)?benchmark.h(>|\")\\s*?"};
} // namespace patterns

constexpr bool isCatch2(std::string_view sv) noexcept {
	return ctre::match<patterns::catch2_pattern>(sv);
}

constexpr bool isGtest(std::string_view sv) noexcept {
	return ctre::match<patterns::gtest_pattern>(sv);
}

constexpr bool isBenchmark(std::string_view sv) noexcept {
	return ctre::match<patterns::benchmark_pattern>(sv);
}
} // namespace cpp

namespace python {
namespace patterns {
static constexpr auto unittest0_pattern =
    ctll::fixed_string{"^import unittest( as (.*)?)?$"};

static constexpr auto unittest1_pattern =
    ctll::fixed_string{"^from unittest import (.*)?$"};
} // namespace patterns

constexpr bool isUnittest(std::string_view sv) noexcept {
	return ctre::match<patterns::unittest0_pattern>(sv) ||
	       ctre::match<patterns::unittest1_pattern>(sv);
}
} // namespace python
