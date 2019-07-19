#pragma once

#include "ctre.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

template <typename T>
std::string parseFile(std::string_view filename, T functions) {
	std::string output = "hi";
	std::string line;
	std::ifstream infile(std::string(filename).c_str());
	while (std::getline(infile, line)) {
		std::cout << "Process line: " << line << '\n';
		if (std::any_of(
		        functions.begin(), functions.end(),
		        [&line](const auto &function) { return function(line); })) {
			return output;
		}
	}
	return "Found nothing.";
}

