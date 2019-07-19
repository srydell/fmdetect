#include "get_special_filetype.h"
#include "matchers.h"
#include <array>
#include <functional>
#include <string_view>
#include <vector>

int main() {
	auto matchFunctions = std::array<std::function<bool(std::string_view)>, 2>(
	    {cpp::matchers::isCatch2, cpp::matchers::isGtest});
	std::cout << parseFile("test/testfiles/catch2/010-TestCase.cpp",
	                       matchFunctions)
	          << '\n';
}
