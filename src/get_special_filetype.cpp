#include "get_special_filetype.h"
#include "filetypeMatcher.h"
#include "matchers.h"
#include <array>

int main() {
	auto p1 = FiletypeMatcher("catch2", cpp::isCatch2);
	auto p2 = FiletypeMatcher("gtest", cpp::isGtest);
	std::array<FiletypeMatcher, 2> s = {p1, p2};
	std::cout << parseFile("test/testfiles/catch2/010-TestCase.cpp", s) << '\n';
	std::cout << parseFile("test/testfiles/gtest/sample1_unittest.cc", s)
	          << '\n';
}
