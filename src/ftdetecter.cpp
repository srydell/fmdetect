#include "filetype_matcher.h"
#include <clara.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> parsePaths(const std::string &paths) {
	std::vector<std::string> parsed;
	std::string path;
	std::istringstream tokenStream(paths);
	while (std::getline(tokenStream, path, ',')) {
		parsed.push_back(path);
	}
	return parsed.empty() ? std::vector({paths}) : parsed;
}

int main(int argc, char **argv) {
	std::string preliminaryFiletype;
	std::string paths;
	bool showHelp = false;
	auto cli = clara::Help(showHelp) |
	           clara::Opt(preliminaryFiletype, "filetype")["-f"]["--filetype"](
	               "What is the current filetype? E.g. cpp") |
	           clara::Opt(paths, "paths")["-p"]["--paths"](
	               "Path(s) to the file being examined. May be multiple "
	               "separated by a comma (,).");

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
		if (auto specialFiletype = SpecialFiletype::getSpecialFiletype(
		        preliminaryFiletype, path)) {
			std::cout << specialFiletype.value() << '\n';
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}
