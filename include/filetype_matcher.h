#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace SpecialFiletype {
/**
 * @brief: Setup the correct matchers for the given filetype
 *         and see if any of them matches the content of the file
 *
 * @param: std::string_view initialFiletype
 *       : std::string_view filename
 *
 * @return: std::optional<std::string>
 */
std::optional<std::string> getSpecialFiletype(std::string_view initialFiletype,
                                              std::string_view filename);
} // namespace SpecialFiletype
