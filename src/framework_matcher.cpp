#include "FrameworkMatcher/framework_matcher.h"
#include "Helpers/matcher_helpers.h"
#include "matchers.h"
#include <array>
#include <optional>
#include <string>
#include <string_view>

namespace FrameworkMatcher {
std::optional<std::string> getFrameworkUsed(std::string_view initialFiletype,
                                            std::string_view filename) {
	using Helpers::Matcher;
	if (initialFiletype == "cpp") {
		auto possibleMatchers = std::array<Matcher, 3>(
		    {Matcher("catch2", cpp::isCatch2), Matcher("gtest", cpp::isGtest),
		     Matcher("benchmark", cpp::isBenchmark)});
		return parseFile(filename, possibleMatchers);
	} else if (initialFiletype == "python") {
		auto possibleMatchers = std::array<Matcher, 2>({
		    Matcher("unittest", python::isUnittest),
		    Matcher("pytest", python::isPytest),
		});
		return parseFile(filename, possibleMatchers);
	}
	return {};
}
} // namespace FrameworkMatcher
