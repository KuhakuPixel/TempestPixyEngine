from typing import List
import subprocess
import sys
import os


pythonVersion = sys.version_info
# print("version of python {0}".format(pythonVersion))


if pythonVersion.major < 3 and pythonVersion.minor < 5:
    print("version is not compatable")
    print(
        "version of python :"
        + str(pythonVersion.major)
        + "."
        + str(pythonVersion.minor)
        + "."
        + str(pythonVersion.micro)
    )
    print("version must at least be 3.5 or greater")
    exit()


def compile_cpp_codes(
    source_folders: List[str], build_path: str, file_name: str, debug: bool = False
):
    codesFiles = []
    for folder in source_folders:
        for file in os.listdir(folder):
            filePath = os.path.join(folder, file)
            file_extension = os.path.splitext(filePath)[1]
            if os.path.isfile(filePath) and file_extension == ".cpp":
                codesFiles.append(filePath)

    commands = ["g++"]
    if debug:
        commands.append("-g")
    commands.extend(codesFiles)
    commands.extend(["-o", os.path.join(build_path, file_name)])
    print("Running : " + " ".join(commands))
    subprocess.run(commands)


compile_cpp_codes(["Src"], "build", "main", debug=False)
