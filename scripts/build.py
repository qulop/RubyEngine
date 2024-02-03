import utility
from utility import CWD, ROOT_FOLDER, ENGINE_NAME
import afterbuild
import rparser

import os
import sys
import shutil
import subprocess
from typing import Union
from pathlib import Path


class Builder:
    @staticmethod
    def build_dll(config_cmake_cmd: str, build_cmake_cmd: str) -> int:
        source_dir = CWD.get()

        os.chdir(ROOT_FOLDER.get())
        utility.go_to_build_directory()
        engine_name = ENGINE_NAME.get()

        if utility.execute(config_cmake_cmd, build_cmake_cmd) != 0:
            return -1
        
        print(f"\n\n\n\n=== DLL build complete ===\n{engine_name}.dll and {engine_name}.lib located at:")

        find_extensions = ["dll", "lib"]
        pattern = f"{engine_name}.*"
        path = f"{ROOT_FOLDER.get()}\\build"
        for file in utility.find_recursive(path, pattern, find_extensions):
            print(f"\t-- {file[1]}")

        os.chdir(source_dir)

        return 0
    

    @staticmethod
    def build_playground(config_cmake_cmd: str, build_cmake_cmd: str) -> Union[int, str]:
        # Move RubyEngine.dll(.lib) to playground\
        extensions = ["dll", "lib"]
        pattern = f"{ENGINE_NAME.get()}.*"
        dir = f"{ROOT_FOLDER.get()}\\build"

        for name, path in utility.find_recursive(dir, pattern, extensions):
            shutil.move(path, f"{ROOT_FOLDER.get()}\\playground\\{name}")

        os.chdir(f"{ROOT_FOLDER.get()}/playground/")
        utility.go_to_build_directory()

        if utility.execute(config_cmake_cmd, build_cmake_cmd) != 0:
            return -1

        # Expending in [(fileName, path)] -> (fileName, path) -> fileName -> fileName.parent
        #                                          [0]             [1]         <...>.parent
        target_executable_loc = utility.find_recursive(
            f"{ROOT_FOLDER.get()}\\playground\\build", "RubyDemo.exe", ["exe"])[0][1].parent
        # ^ Location of Playground exe 

        shutil.move(f"{ROOT_FOLDER.get()}\\playground\\{ENGINE_NAME.get()}.dll", f"{target_executable_loc}\\{ENGINE_NAME.get()}.dll")
        os.chdir(CWD.get())

        print(f"\n\n\n\n=== Playground build complete ====\nRubyDemo.exe located at {target_executable_loc}\\RubyDemo.exe")

        return str(target_executable_loc)


    @staticmethod
    def build_failed():
        print("=== Build failed ===")
        exit(1)




def main(args: dict) -> None:
    print(f"Selected next build settings:\n\tIS_BUILD_DLL: {args['dll']};\n\tIS_BUILD_PLAYGROUND: {args['pg']}")
    
    playground_loc = None 
   
    if (args["dll"]) and (Builder.build_dll("..", f"--build . --target {ENGINE_NAME.get()}") != 0):
        Builder.build_failed()

    if args["pg"]:
        playground_loc = Builder.build_playground("..", "--build . --target RubyDemo")
        if not isinstance(playground_loc, str):
            Builder.build_failed()

    shaders_location = f"{ROOT_FOLDER.get()}\\ruby\\src\\render\\shaders\\list"
    target_location = f"{playground_loc}\\shaders"

    afterbuild.move_shaders(target_location, shaders_location)
    afterbuild.create_config(playground_loc)


if __name__ == "__main__":
    prsr = rparser.Parser(sys.argv[1:])
    try:
        args = prsr.parse()
        if args != None:
            main(args)
            
    except rparser.ParseException as err:
        print(err)
        

