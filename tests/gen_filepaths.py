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


def gen_filepaths():
    """Create and fill a header file with paths
    :returns: None
    """
    path = pathlib.Path("test_include")
    path.mkdir(exist_ok=True)
    with open(path / "generated_filepaths.h", "w") as header:
        end_file_contents = []
        all_files = []
        for test_dir in pathlib.Path("testfiles").glob("*"):
            test_files = [str(t.resolve()) for t in pathlib.Path(test_dir).glob("*")]
            test_name = test_dir.name
            end_file_contents += wrap_in_vector(test_name, test_files)
            all_files = all_files + test_files

        # Add a final all_files vector
        end_file_contents += wrap_in_vector("all_files", all_files)
        end_file_contents = wrap_in_namespace("testfiles", end_file_contents)
        end_file_contents = add_includes(["vector", "string"], end_file_contents)

        header.writelines(end_file_contents)


if __name__ == "__main__":
    gen_filepaths()
