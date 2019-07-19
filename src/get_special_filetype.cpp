#include "get_special_filetype.h"
#include "filetypeMatcher.h"
#include "matchers.h"
#include <array>
#include <functional>
#include <optional>
#include <string_view>

int main() {
	auto p1 = FiletypeMatcher("catch2", cpp::matchers::isCatch2);
	auto p2 = FiletypeMatcher("gtest", cpp::matchers::isGtest);
	std::array<FiletypeMatcher, 2> s = {p1, p2};
	std::cout << parseFile("test/testfiles/catch2/010-TestCase.cpp", s) << '\n';
}
