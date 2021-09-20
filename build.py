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
    source_folders: List[str],
    build_path: str,
    file_name: str,
    debug: bool = False,
    exclude_cpp_files: List[str] = [],
    object_files: List[str] = [],
):
    codesFiles = []
    codesFiles.extend(object_files)
    for folder in source_folders:
        for file in os.listdir(folder):
            if file in exclude_cpp_files:
                continue
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


args = sys.argv
del args[0]
if len(args) == 0:
    compile_cpp_codes(["Src"], "build", "main", debug=False)
    subprocess.run(["./build/main"])
else:
    if args[0] == "debug":
        compile_cpp_codes(["Src"], "build", "main", debug=True)
        subprocess.run(["./build/main"])

    elif args[0] == "test":
        if not ("TestMain.o" in os.listdir("tests")):
            print("compiling catch2 's library")
            subprocess.run(
                ["g++", "tests/TestMain.cpp", "-c", "-o", "tests/TestMain.o"]
            )

        compile_cpp_codes(
            ["Src", "tests"],
            "tests",
            "test",
            debug=False,
            exclude_cpp_files=["TestMain.cpp", "main.cpp"],
            object_files=["tests/TestMain.o"],
        )
        subprocess.run(["./tests/test"])

    elif args[0] == "debugtest":
        if not ("TestMain.o" in os.listdir("tests")):
            print("compiling catch2 's library")
            subprocess.run(
                ["g++", "tests/TestMain.cpp", "-c", "-o", "tests/TestMain.o"]
            )

        compile_cpp_codes(
            ["Src", "tests"],
            "tests",
            "test",
            debug=True,
            exclude_cpp_files=["TestMain.cpp", "main.cpp"],
            object_files=["tests/TestMain.o"],
        )
        subprocess.run(["./tests/test"])
    else:
        print("unknown command")
