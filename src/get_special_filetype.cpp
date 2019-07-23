#include "get_special_filetype.h"
#include "filetypeMatcher.h"
#include "matchers.h"
#include <array>
#include <clara.hpp>

int main(int argc, char **argv) {
	std::string preliminaryFiletype;
	std::string path;
	bool showHelp = false;
	auto cli = clara::Help(showHelp) |
	           clara::Opt(preliminaryFiletype,
	                      "preliminaryFiletype")["-ft"]["--filetype"](
	               "What is the current filetype? E.g. cpp") |
	           clara::Opt(path, "path")["-p"]["--path"](
	               "Path to the file being examined.");

	auto result = cli.parse(clara::Args(argc, argv));
	if (!result) {
		std::cerr << "Error in command line: " << result.errorMessage()
		          << std::endl;
		return EXIT_FAILURE;
	}

	if (showHelp) {
		std::cout << cli << '\n';
		return EXIT_SUCCESS;
	}

	std::cout << "Filetype is: " << preliminaryFiletype << '\n';
	std::cout << "Path is: " << path << '\n';
}
