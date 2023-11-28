from utility import *

import os
import shutil
import subprocess
from typing import Union
from pathlib import Path

IS_BUILD_DLL        = True
IS_BUILD_DEMO       = True
IS_RUN_AFTER_BUILD  = True


ROOT_FOLDER         = Path(os.path.dirname(__file__)).parent
CWD                 = os.getcwd()

ENGINE_NAME         = "RubyEngine"


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
        print(f"\n\n\n\n-----Build complete-----\n{ENGINE_NAME}.dll and {ENGINE_NAME}.lib located at:")

        for file in findRecursive(f"{ROOT_FOLDER}\\build", f"{ENGINE_NAME}.*"):
            print(f"\t-- {file[1]}")

    os.chdir(sourceDir)

    return 0


def buildDemo(cmakeConfigCmd: str, cmakeBuildCmd: str) -> Union[int, str]:
    # Move RubyEngine.dll(.lib) to demo\
    for name, path in findRecursive(f"{ROOT_FOLDER}\\build", f"{ENGINE_NAME}.*"):
        shutil.move(path, f"{ROOT_FOLDER}\\demo\\{name}")

    os.chdir(f"{ROOT_FOLDER}/demo/")
    changeDirToBuild()

    if execute(cmakeConfigCmd, cmakeBuildCmd) != 0:
        return -1

    # Expending in [(fileName, path)], and then path.parent
    demoExeLocation = findRecursive(f"{ROOT_FOLDER}\\demo\\build", "RubyDemo.exe", ["exe"])[0][1].parent

    shutil.move(f"{ROOT_FOLDER}\\demo\\{ENGINE_NAME}.dll", f"{demoExeLocation}\\{ENGINE_NAME}.dll")
    os.chdir(CWD)

    print(f"\n\n\n\n-----Build complete-----\nRubyDemo.exe located at {demoExeLocation}\\RubyDemo.exe")

    return demoExeLocation



def start() -> None:
    print("Selected next build settings:\n\tIS_BUILD_DLL: {0}\n\tIS_BUILD_DEMO: {1}\n\t\tIS_RUN_AFTER_BUILD: {2}"
                .format(IS_BUILD_DLL, IS_BUILD_DEMO, IS_RUN_AFTER_BUILD))
    
    demoLocation = None

    if IS_RUN_AFTER_BUILD and not IS_BUILD_DEMO:
        print("---- Supposed, that RubyDemo.exe has already been compiled ----")
        demoLocation = findRecursive(f"{ROOT_FOLDER}\\demo\\build", "RubyDemo.*", ["exe"])[0][1].parent

    if IS_BUILD_DLL and buildDll("..", f"--build . --target {ENGINE_NAME}") != 0:
        return

    if IS_BUILD_DEMO:
        demoLocation = buildDemo("..", "--build . --target RubyDemo")
        if not isinstance(demoLocation, str):
            return

    if IS_RUN_AFTER_BUILD:
        subprocess.call([f"{demoLocation}\\RubyDemo"])
        

if __name__ == "__main__":
    start()