import utility
import afterbuild

import os
import shutil
import subprocess
from typing import Union
from pathlib import Path

IS_BUILD_DLL        = True
IS_BUILD_PLAYGROUND = True

ROOT_FOLDER         = Path(os.path.dirname(__file__)).parent
CWD                 = os.getcwd()

ENGINE_NAME         = "RubyEngine"


def buildDll(cmakeConfigCmd: str, cmakeBuildCmd: str) -> int:
    sourceDir = CWD

    os.chdir(ROOT_FOLDER)
    utility.changeDirToBuild()

    if utility.execute(cmakeConfigCmd, cmakeBuildCmd) != 0:
        return -1
    
    locations = []

    for location in locations:
        shutil.move(f"{ROOT_FOLDER}\\playground\\{location.name}")

    if not IS_BUILD_PLAYGROUND:
        print(f"\n\n\n\n=== Build complete ===\n{ENGINE_NAME}.dll and {ENGINE_NAME}.lib located at:")

        for file in utility.findRecursive(f"{ROOT_FOLDER}\\build", f"{ENGINE_NAME}.*"):
            print(f"\t-- {file[1]}")

    os.chdir(sourceDir)

    return 0


def buildPlayground(cmakeConfigCmd: str, cmakeBuildCmd: str) -> Union[int, str]:
    # Move RubyEngine.dll(.lib) to playground\
    for name, path in utility.findRecursive(f"{ROOT_FOLDER}\\build", f"{ENGINE_NAME}.*"):
        shutil.move(path, f"{ROOT_FOLDER}\\playground\\{name}")

    os.chdir(f"{ROOT_FOLDER}/playground/")
    utility.changeDirToBuild()

    if utility.execute(cmakeConfigCmd, cmakeBuildCmd) != 0:
        return -1

    # Expending in [(fileName, path)], and then path.parent
    playgroundExeLocation = utility.findRecursive(f"{ROOT_FOLDER}\\playground\\build", "RubyDemo.exe", ["exe"])[0][1].parent

    shutil.move(f"{ROOT_FOLDER}\\playground\\{ENGINE_NAME}.dll", f"{playgroundExeLocation}\\{ENGINE_NAME}.dll")
    os.chdir(CWD)

    print(f"\n\n\n\n=== Build complete ====\nRubyDemo.exe located at {playgroundExeLocation}\\RubyDemo.exe")

    return playgroundExeLocation.__str__()



def main() -> None:
    print("Selected next build settings:\n\tIS_BUILD_DLL: {0};\n\IS_BUILD_PLAYGROUND: {1}."
                .format(IS_BUILD_DLL, IS_BUILD_PLAYGROUND))
    
    playgroundLocation = None

    # if IS_RUN_AFTER_BUILD and not IS_BUILD_PLAYGROUND:
        # print("---- Supposed, that RubyDemo.exe has already been compiled ----")
        # playgroundLocation = utility.findRecursive(f"{ROOT_FOLDER}\\playground\\build", "RubyDemo.*", ["exe"])[0][1].parent

    if IS_BUILD_DLL and buildDll("..", f"--build . --target {ENGINE_NAME}") != 0:
        print("=== Build failed ===")
        return

    if IS_BUILD_PLAYGROUND:
        playgroundLocation = buildPlayground("..", "--build . --target RubyDemo")
        if not isinstance(playgroundLocation, str):
            return

    shadersLocation = f"{ROOT_FOLDER}\\ruby\\src\\render\\shaders\\list"
    targetLocation = f"{playgroundLocation}\\shaders"
    afterbuild.moveShaders(targetLocation, shadersLocation)
        

if __name__ == "__main__":
    main()