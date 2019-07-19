#pragma once

#include "matchers.h"
#include <array>
#include <functional>
#include <optional>
#include <string_view>
#include <string>

struct FiletypeMatcher {
	FiletypeMatcher(std::string_view ft, decltype(cpp::matchers::isCatch2) &m)
	    : m_filetype(std::string(ft)), m_isFiletype(m) {}

	std::optional<std::string> operator()(std::string_view text) const {
		if (m_isFiletype(text)) {
			return m_filetype;
		}
		return std::nullopt;
	}

	std::string m_filetype;
	decltype(cpp::matchers::isCatch2) &m_isFiletype;
};
