#pragma once

#include "ctre.hpp"

namespace cpp::patterns {
static constexpr auto catch_pattern =
	ctll::fixed_string{"#include ?(<|\")(catch2/)?catch.hpp(>|\")\\s*?"};

static constexpr auto gtest_pattern =
    ctll::fixed_string{"#include ?(<|\")(gtest/)?gtest.h(>|\")\\s*?"};

static constexpr auto benchmark_pattern =
    ctll::fixed_string{"#include ?(<|\")(catch2/)?catch.hpp(>|\")\\s*?"};

} // namespace cpp::patterns
