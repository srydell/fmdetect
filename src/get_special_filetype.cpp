#include "filetype_matcher.h"
#include <clara.hpp>
#include <iostream>

int main(int argc, char **argv) {
	std::string preliminaryFiletype;
	std::string path;
	bool showHelp = false;
	auto cli = clara::Help(showHelp) |
	           clara::Opt(preliminaryFiletype, "filetype")["-f"]["--filetype"](
	               "What is the current filetype? E.g. cpp") |
	           clara::Opt(path, "path")["-p"]["--path"](
	               "Path to the file being examined.");

	auto result = cli.parse(clara::Args(argc, argv));
	if (!result) {
		std::cerr << "Error in command line: " << result.errorMessage()
		          << std::endl;
		return EXIT_FAILURE;
	}

	if (showHelp || path.empty() || preliminaryFiletype.empty()) {
		std::cout << cli << '\n';
		return EXIT_SUCCESS;
	}

	if (auto specialFiletype = getSpecialFiletype(preliminaryFiletype, path)) {
		std::cout << specialFiletype.value() << '\n';
	}
}
