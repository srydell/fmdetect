#pragma once

#include "Helpers/matcher_helpers.h"
#include "ctre.hpp"
#include <array>
#include <string_view>

namespace Matchers::Elixir {
namespace {
static constexpr auto exunit_pattern =
    ctll::fixed_string {"^(\\s*?)(use|import) ExUnit(\\..*?)$"};
}    // namespace

constexpr bool isExUnit(std::string_view sv) noexcept {
	return ctre::match<exunit_pattern>(sv);
}

auto getMatchers() noexcept {
	using Helpers::Matcher;
	return std::array<Matcher<decltype(isExUnit)>, 1>({
	    Matcher("exunit", isExUnit),
	});
}
}    // namespace Matchers::Elixir
