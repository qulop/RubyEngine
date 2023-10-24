# TODO:
#   - Build glad and glfw3 only if .lib files is absent 


from utility import *

import os
import shutil
import subprocess
from pathlib import Path

IS_RUN_AFTER_BUILD  = False
IS_BUILD_DLL        = False
IS_BUILD_DEMO       = True


ROOT_FOLDER         = Path(os.path.dirname(__file__)).parent
CWD                 = os.getcwd()



def buildDll(cmakeConfigCmd: str, cmakeBuildCmd: str) -> int:
    sourceDir = os.getcwd()

    os.chdir(ROOT_FOLDER)
    changeDirToBuild()

    if execute(cmakeConfigCmd, cmakeBuildCmd) != 0:
        return -1
    
    locations = []

    for location in locations:
        shutil.move(f"{ROOT_FOLDER}\\demo\\{location.name}")

    if not IS_BUILD_DEMO:
        print("\n\n\n\n-----Build complete-----\nRubyVn.dll and RubyVn.lib located at:")

        for file in findRecursive(f"{ROOT_FOLDER}\\build", "RubyVn.*"):
            print(f"\t-- {file[1]}")

    os.chdir(sourceDir)

    return 0


def buildDemo(cmakeConfigCmd: str, cmakeBuildCmd: str) -> int:
    # Move RubyVn.dll(.lib) to demo\
    for name, path in findRecursive(f"{ROOT_FOLDER}\\build", "RubyVn.*"):
        shutil.move(path, f"{ROOT_FOLDER}\\demo\\{name}")

    os.chdir(f"{ROOT_FOLDER}/demo/")
    changeDirToBuild()

    if execute(cmakeConfigCmd, cmakeBuildCmd) != 0:
        return -1

    # Expending in [(fileName, path)], and then path.parent
    demoExeLocation = findRecursive(f"{ROOT_FOLDER}\\demo\\build", "RubyDemo.exe", ["exe"])[0][1].parent

    shutil.move(f"{ROOT_FOLDER}\\demo\\RubyVn.dll", f"{demoExeLocation}\\RubyVn.dll")
    os.chdir(CWD)

    print(f"\n\n\n\n-----Build complete-----\nRubyDemo.exe located at {demoExeLocation}\\RubyDemo.exe")

    return 0



def start():
    print("Selected next build settings:\n\tIS_RUN_AFTER_BUILD: NOT_AVAIL\n\tIS_BUILD_DLL: {0}\n\tIS_BUILD_DEMO: {1}"
                .format(IS_BUILD_DLL, IS_BUILD_DEMO))

    if IS_BUILD_DLL and buildDll("..", "--build . --target RubyVn") != 0:
        return

    if IS_BUILD_DEMO and buildDemo("..", "--build . --target RubyDemo") != 0:
        return

    # TODO:
    # if IS_RUN_AFTER_BUILD:
    # subprocess.call(["../demo/build/demo/Debug/RubyDemo"])
        

if __name__ == "__main__":
    start()