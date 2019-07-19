#include "ctre.hpp"
#include "patterns.h"
#include <string_view>

namespace cpp::matchers {
constexpr bool isCatch2(std::string_view sv) noexcept {
	return ctre::match<cpp::patterns::catch_pattern>(sv);
}

constexpr bool isGtest(std::string_view sv) noexcept {
	return ctre::match<cpp::patterns::gtest_pattern>(sv);
}

constexpr bool isBenchmark(std::string_view sv) noexcept {
	return ctre::match<cpp::patterns::benchmark_pattern>(sv);
}
}
