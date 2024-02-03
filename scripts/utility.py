from pathlib import Path
import subprocess
import os


class ConstantView:
    def __init__(self, value):
        self.__value = value

    def get(self):
        return self.__value
    
    def __str__(self):
        return self.__value.__str__()
    

ROOT_FOLDER         = ConstantView(Path(os.path.dirname(__file__)).parent)
CWD                 = ConstantView(os.getcwd())

ENGINE_NAME         = ConstantView("RubyEngine")


# - Searches recursively files with specified pattern
#       and extesions, starting from <dir>.
# - Return list of tuples: 
#       First element of tuple is file name
#       Second element is absolute path to this file
def find_recursive(dir: str, pattern: str, extensions: list = None) -> list:
    result = []
    append_to_result = lambda file, path: result.append((file, path))

    for path in Path(dir).rglob(pattern):
        file = path.name

        splitted_name = path.name.split(".")

        # For filter files with several extensions. For example, RubyEngine.*.*
        if len(splitted_name) > 2:
            continue

        if extensions == None:
            append_to_result(file, path)
            continue

        startswith = file.startswith(pattern.split(".")[0])
        if startswith and splitted_name[1] in extensions:
            append_to_result(file, path)

    return result


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