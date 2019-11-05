#include "FrameworkMatcher/framework_matcher.h"
#include <clara.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {
std::vector<std::string> parsePaths(const std::string &paths) {
	std::vector<std::string> parsed;
	std::string path;
	std::istringstream tokenStream(paths);
	while (std::getline(tokenStream, path, ',')) {
		parsed.push_back(path);
	}
	return parsed.empty() ? std::vector({paths}) : parsed;
}
} // namespace

int main(int argc, char **argv) {
	std::string preliminaryFiletype;
	std::string paths;
	bool showHelp = false;
	auto cli = clara::Help(showHelp) |
	           clara::Opt(preliminaryFiletype, "filetype")["-f"]["--filetype"](
	               "What is the current filetype? E.g. cpp") |
	           clara::Opt(paths, "paths")["-p"]["--paths"](
	               "Path(s) to the file(s) being examined. "
	               "May be multiple separated by a comma (,).");

	auto result = cli.parse(clara::Args(argc, argv));
	if (!result) {
		std::cerr << "Error in command line: " << result.errorMessage() << '\n';
		return EXIT_FAILURE;
	}

	if (showHelp || paths.empty() || preliminaryFiletype.empty()) {
		std::cout << cli << '\n';
		return EXIT_SUCCESS;
	}

	for (const auto &path : parsePaths(paths)) {
		if (auto foundFramework =
		        FrameworkMatcher::getFrameworkUsed(preliminaryFiletype, path)) {
			std::cout << foundFramework.value() << '\n';
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}
