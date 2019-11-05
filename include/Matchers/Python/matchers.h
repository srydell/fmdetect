#pragma once

#include "Helpers/matcher_helpers.h"
#include "ctre.hpp"
#include <array>
#include <string_view>

namespace Matchers::Python {
namespace {
static constexpr auto unittest0_pattern =
    ctll::fixed_string{"^import unittest( as (.*)?)?$"};

static constexpr auto unittest1_pattern =
    ctll::fixed_string{"^from unittest import (.*)?$"};

static constexpr auto pytest0_pattern =
    ctll::fixed_string{"^import pytest( as (.*)?)?$"};

static constexpr auto pytest1_pattern =
    ctll::fixed_string{"^from pytest import (.*)?$"};
}    // namespace

constexpr bool isUnittest(std::string_view sv) noexcept {
	return ctre::match<unittest0_pattern>(sv) ||
	       ctre::match<unittest1_pattern>(sv);
}

constexpr bool isPytest(std::string_view sv) noexcept {
	return ctre::match<pytest0_pattern>(sv) || ctre::match<pytest1_pattern>(sv);
}

auto getMatchers() noexcept {
	using Helpers::Matcher;
	return std::array<Matcher<decltype(isUnittest)>, 2>(
	    {Matcher("unittest", isUnittest), Matcher("pytest", isPytest)});
}

}    // namespace Matchers::Python
