#pragma once

#include "ctre.hpp"
#include "matchers.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

namespace Helpers {
struct FiletypeMatcher {
	FiletypeMatcher(std::string_view ft, decltype(cpp::isCatch2) &m)
	    : m_filetype(std::string(ft)), m_isFiletype(m) {}

	std::optional<std::string> operator()(std::string_view text) const {
		if (m_isFiletype(text)) {
			return m_filetype;
		}
		return std::nullopt;
	}

	std::string m_filetype;
	decltype(cpp::isCatch2) &m_isFiletype;
};

template <typename MatchFunctions>
std::optional<std::string> parseFile(std::string_view filename,
                                     MatchFunctions functions) {
	std::string line;
	std::ifstream infile(std::string(filename).c_str());
	if (infile.is_open()) {
		while (std::getline(infile, line)) {
			for (auto &f : functions) {
				if (auto ft = f(line)) {
					return ft.value();
				}
			}
		}
	}
	return {};
}

} // namespace Helpers
