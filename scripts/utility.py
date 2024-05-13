from pathlib import Path
import shutil
import subprocess
import os


class ConstantView:
    def __init__(self, value):
        self.__value = value

    def get(self):
        return self.__value
    
    def __str__(self):
        return str(self.__value)
    

ROOT_FOLDER = ConstantView(Path(os.path.dirname(__file__)).parent)
CALL_DIR = ConstantView(os.getcwd())

ENGINE_NAME = ConstantView("RubyEngine")
PLAYGROUND_NAME = ConstantView("RubyDemo")


# - Searches recursively files with specified pattern
#       and extesions, starting from <directory>.
# - Return list of tuples: 
#       First element of tuple is file name
#       Second element is absolute path to this file
def find_recursive(directory: str, pattern: str, extensions: list = None) -> list:
    result = []
    append_to_result = lambda f, p: result.append((f, p))

    for path in Path(directory).rglob(pattern):
        file = path.name

        splitted_name = path.name.split(".")

        # For filter files with several extensions. For example, RubyEngine.*.*
        if len(splitted_name) > 2:
            continue

        if not extensions:
            append_to_result(file, path)
            continue

        startswith = file.startswith(pattern.split(".")[0])
        if startswith and splitted_name[1] in extensions:
            append_to_result(file, path)

    return result


def move_file_to(filename: str, file_dir: str, destination: str) -> None:
    full_file_path = f"{file_dir}\\{filename}"

    shutil.move(full_file_path, f"{destination}\\{filename}")


def go_to_build_directory():
    if not os.path.isdir("build"):
        os.mkdir("build")
    os.chdir("build/")


def execute(conf: str, build: str) -> int:
    config_code = subprocess.call(["cmake"] + conf.split())
    build_code = subprocess.call(["cmake"] + build.split())
    if config_code != 0 or build_code != 0:
        return -1
    return 0
