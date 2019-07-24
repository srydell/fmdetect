#include "filetype_matcher.h"
#include "matcher_helpers.h"
#include "matchers.h"
#include <array>
#include <optional>
#include <string>
#include <string_view>

namespace SpecialFiletype {
std::optional<std::string> getSpecialFiletype(std::string_view initialFiletype,
                                              std::string_view filename) {
	using Helpers::FiletypeMatcher;
	if (initialFiletype == "cpp") {
		auto possibleMatchers = std::array<FiletypeMatcher, 3>(
		    {FiletypeMatcher("catch2", cpp::isCatch2),
		     FiletypeMatcher("gtest", cpp::isGtest),
		     FiletypeMatcher("benchmark", cpp::isBenchmark)});
		return parseFile(filename, possibleMatchers);
	}
	return {};
}
} // namespace SpecialFiletype
