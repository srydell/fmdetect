"""
Brief:               Generate a header file containing the paths to all test files in (testfiles/*)

File name:           gen_filepaths.py
Author:              Simon Rydell
Python Version:      3.7
"""

import pathlib


def add_includes(includes, lines):
    """Add include statements before lines

    :includes: List
    :lines: List
    :returns: lines with includes added before
    """
    includes.reverse()
    for include in includes:
        lines.insert(0, f"#include <{include}>\n")
    return lines


def wrap_in_array(array_name, contents):
    """Create an array containing the contents
       Ex:
           std::array<std::string, {len(contents)}> {array_name} = {
           "content0",
           "content1",
           };
    :returns: wrapped contents
    """
    contents = [f'    "{content}",\n' for content in contents]
    # Remove trailing ',' on the last input in array
    contents[-1] = f"{contents[-1][:-2]}"

    contents.insert(
        0, f"\nstd::array<std::string, {len(contents)}> {array_name} = " + "{\n"
    )
    contents.append("\n};\n\n")
    return contents


def wrap_in_namespace(namespace, lines):
    """Create a namespace around the given lines:
       Ex:
           namspace {namespace} {
           line0
           line1
           }
    :lines: list of strings
    :returns: wrapped lines
    """
    lines.insert(0, f"namespace {namespace} " + "{\n")
    lines.append("}\n")
    return lines


def gen_filepaths():
    """Create and fill a header file with paths
    :returns: None
    """
    pathlib.Path("test/test_include").mkdir(exist_ok=True)
    with open("test/test_include/generated_filepaths.h", "w") as header:
        lines = []
        for test_dir in pathlib.Path("test/testfiles/").glob("*"):
            test_files = [str(t) for t in pathlib.Path(test_dir).glob("*")]
            test_name = test_dir.name
            lines += wrap_in_array(test_name, test_files)
        lines = wrap_in_namespace("testfiles", lines)
        lines = add_includes(["array", "string"], lines)
        header.writelines(lines)


if __name__ == "__main__":
    gen_filepaths()
