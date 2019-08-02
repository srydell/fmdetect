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


def wrap_in_vector(vector_name, contents):
    """Create an vector containing the contents
       Ex:
           std::vector<std::string> {vector_name} = {
           "content0",
           "content1",
           };
    :returns: wrapped contents
    """
    contents = [f'    "{content}",\n' for content in contents]
    # Remove trailing ',' on the last input in array
    contents[-1] = f"{contents[-1][:-2]}"

    contents.insert(0, f"\nstd::vector<std::string> {vector_name} = " + "{\n")
    contents.append("\n};\n\n")
    return contents


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


def concat_lists(list0, list1):
    """Return concatenated version of the two lists

    :list0: List - The first in the new list
    :list1: List - The last in the new list
    :returns: List - Concatenated list
    """
    for item in list1:
        list0.append(item)
    return list0


def gen_filepaths():
    """Create and fill a header file with paths
    :returns: None
    """
    pathlib.Path("test_include").mkdir(exist_ok=True)
    with open("test_include/generated_filepaths.h", "w") as header:
        lines = []
        all_files = []
        for test_dir in pathlib.Path("testfiles").glob("*"):
            test_files = [str(t.resolve()) for t in pathlib.Path(test_dir).glob("*")]
            all_files = concat_lists(all_files, test_files)
            test_name = test_dir.name
            lines += wrap_in_vector(test_name, test_files)
        lines += wrap_in_vector("all_files", all_files)
        lines = wrap_in_namespace("testfiles", lines)
        lines = add_includes(["vector", "string"], lines)
        header.writelines(lines)


if __name__ == "__main__":
    gen_filepaths()
