#include "get_special_filetype.h"
#include "matchers.h"
#include <array>
#include <functional>
#include <optional>
#include <string_view>

struct FiletypeMatcher {
	FiletypeMatcher(std::string_view ft, decltype(cpp::matchers::isCatch2) &m)
	    : m_filetype(std::string(ft)), m_isFiletype(m) {}

	std::optional<std::string> operator()(std::string_view line) const {
		if (m_isFiletype(line)) {
			return m_filetype;
		}
		return std::nullopt;
	}

	std::string m_filetype;
	decltype(cpp::matchers::isCatch2) &m_isFiletype;
};

int main() {
	auto p1 = FiletypeMatcher("catch2", cpp::matchers::isCatch2);
	auto p2 = FiletypeMatcher("gtest", cpp::matchers::isGtest);
	std::array<FiletypeMatcher, 2> s = {p1, p2};
	std::cout << parseFile("test/testfiles/catch2/010-TestCase.cpp", s) << '\n';
}
