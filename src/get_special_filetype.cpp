#include "get_special_filetype.h"
#include "filetypeMatcher.h"
#include "matchers.h"
#include <array>

int main(int argc, char **argv) {
	std::cout << "You have entered " << argc << " arguments:"
	          << "\n";

	for (int i = 1; i < argc; ++i)
		std::cout << argv[i] << "\n";
}
