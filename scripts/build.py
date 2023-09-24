import opengl_check

import os
import shutil
import subprocess

IS_RUN_AFTER_BUILD  = False
IS_BUILD_DLL        = True
IS_BUILD_DEMO       = True

CWD                 = os.getcwd()


def changeDirToBuild():
    if not os.path.isdir("build"):
        os.mkdir("build")
    os.chdir("build/")

def execute(conf: str, build: str) -> int:
    configCode = subprocess.call(["cmake"] + conf.split())
    buildCode = subprocess.call(["cmake"] + build.split())
    if configCode != 0 or buildCode != 0:
        return -1
    return 0



def buildDll(cmakeConfigCmd: str, cmakeBuildCmd: str) -> int:
    os.chdir("../")

    changeDirToBuild()

    if execute(cmakeConfigCmd, cmakeBuildCmd) != 0:
        return -1

    shutil.move(f"{CWD}\\ruby\\Debug\\RubyVn.dll", f"{CWD}\\..\\demo\\RubyVn.dll")
    shutil.move(f"{CWD}\\ruby\\Debug\\RubyVn.lib", f"{CWD}\\..\\demo\\RubyVn.lib")
    os.chdir("../scripts/")

    return 0


def buildDemo(cmakeConfigCmd, cmakeBuildCmd):
    os.chdir("../demo/")

    changeDirToBuild()

    if execute(cmakeConfigCmd, cmakeBuildCmd) != 0:
        return -1

    shutil.move(f"{CWD}\\..\\RubyVn.dll", f"{CWD}\\demo\\Debug\\RubyVn.dll")
    os.chdir("../../scripts/")

    return 0



def start():
    print("You was changed next build settings:\n\tIS_RUN_AFTER_BUILD: {0}\n\tIS_BUILD_DLL: {1}\n\tIS_BUILD_DEMO: {2}"
                .format(IS_RUN_AFTER_BUILD, IS_BUILD_DLL, IS_BUILD_DEMO))

    if IS_BUILD_DLL and buildDll("..", "--build . --target RubyVn") != 0:
        return

    if IS_BUILD_DEMO and buildDemo("..", "--build . --target RubyDemo") != 0:
        return

    if IS_RUN_AFTER_BUILD:
        subprocess.call(["../demo/build/demo/Debug/RubyDemo"])
        
start()