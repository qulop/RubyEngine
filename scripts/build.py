import utility
from utility import View
import afterbuild

import os
import shutil
import subprocess
from typing import Union
from pathlib import Path


IS_BUILD_DLL        = View(True)
IS_BUILD_PLAYGROUND = View(True)

ROOT_FOLDER         = View(Path(os.path.dirname(__file__)).parent)
CWD                 = View(os.getcwd())

ENGINE_NAME         = View("RubyEngine")


class Builder:
    @staticmethod
    def build_dll(config_cmake_cmd: str, build_cmake_cmd: str) -> int:
        source_dir = CWD.get()

        os.chdir(ROOT_FOLDER.get())
        utility.go_to_build_directory()

        if utility.execute(config_cmake_cmd, build_cmake_cmd) != 0:
            return -1
        
        locations = []
        for location in locations:
            shutil.move(f"{ROOT_FOLDER.get()}\\playground\\{location.name}")

        print(f"\n\n\n\n=== DLL build complete ===\n{ENGINE_NAME.get()}.dll and {ENGINE_NAME.get()}.lib located at:")
        for file in utility.find_recursive(f"{ROOT_FOLDER.get()}\\build", f"{ENGINE_NAME.get()}.*"):
            print(f"\t-- {file[1]}")

        os.chdir(source_dir)

        return 0
    
    @staticmethod
    def build_playground(config_cmake_cmd: str, build_cmake_cmd: str) -> Union[int, str]:
            # Move RubyEngine.dll(.lib) to playground\
        for name, path in utility.find_recursive(f"{ROOT_FOLDER.get()}\\build", f"{ENGINE_NAME.get()}.*"):
            shutil.move(path, f"{ROOT_FOLDER.get()}\\playground\\{name}")

        os.chdir(f"{ROOT_FOLDER.get()}/playground/")
        utility.go_to_build_directory()

        if utility.execute(config_cmake_cmd, build_cmake_cmd) != 0:
            return -1

        # Expending in [(fileName, path)], and then path.parent
        target_executable_loc = utility.find_recursive(f"{ROOT_FOLDER.get()}\\playground\\build", "RubyDemo.exe", ["exe"])[0][1].parent
        # ^ Location of Playground exe 

        shutil.move(f"{ROOT_FOLDER.get()}\\playground\\{ENGINE_NAME.get()}.dll", f"{target_executable_loc}\\{ENGINE_NAME.get()}.dll")
        os.chdir(CWD.get())

        print(f"\n\n\n\n=== Playground build complete ====\nRubyDemo.exe located at {target_executable_loc}\\RubyDemo.exe")

        return target_executable_loc.__str__()


def build_failed():
    print("=== Build failed ===")
    exit(1)


def main() -> None:
    print("Selected next build settings:\n\tIS_BUILD_DLL.get(): {0};\n\IS_BUILD_PLAYGROUND.get(): {1}."
                .format(IS_BUILD_DLL.get(), IS_BUILD_PLAYGROUND.get()))

    playground_loc = None 
   
    if (IS_BUILD_DLL.get()) and (Builder.build_dll("..", f"--build . --target {ENGINE_NAME.get()}") != 0):
        build_failed()

    if IS_BUILD_PLAYGROUND.get():
        playground_loc = Builder.build_playground("..", "--build . --target RubyDemo")
        if not isinstance(playground_loc, str):
            build_failed

    shaders_location = f"{ROOT_FOLDER.get()}\\ruby\\src\\render\\shaders\\list"
    target_location = f"{playground_loc}\\shaders"

    afterbuild.move_shaders(target_location, shaders_location)
    afterbuild.create_config(playground_loc)
        

if __name__ == "__main__":
    main()