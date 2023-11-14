from pathlib import Path
import subprocess
import os


# - Searches recursively files with specified pattern
#       and extesions, starting from <dir>.
# - Return list of tuples: 
#       First element of tuple is file name
#       Second element is absolute path to this file
def findRecursive(dir: str, pattern: str, extensions: list = ["dll", "lib"]) -> list:
    result = []

    for path in Path(dir).rglob(pattern):
        file = path.name

        splittedName = path.name.split(".")

        # For filter files with several extensions. For example, RubyEngine.*.*
        if len(splittedName) > 2:
            continue

        if file.startswith(pattern.split(".")[0]) and splittedName[1] in extensions:
            result.append((file, path))

    return result


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