#include "FrameworkMatcher/framework_matcher.h"
#include "Helpers/matcher_helpers.h"
#include "Matchers/Cpp/matchers.h"
#include "Matchers/Python/matchers.h"
#include <array>
#include <optional>
#include <string>
#include <string_view>

namespace FrameworkMatcher {
std::optional<std::string> getFrameworkUsed(std::string_view initialFiletype,
                                            std::string_view filename) {
	using Helpers::Matcher;
	if (initialFiletype == "cpp") {
		return parseFile(filename, Matchers::Cpp::getMatchers());
	} else if (initialFiletype == "python") {
		return parseFile(filename, Matchers::Python::getMatchers());
	}
	return {};
}
} // namespace FrameworkMatcher
