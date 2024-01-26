import utility

import shutil
import pathlib
import os


class Path(pathlib.Path):
    def __str__(self):
        return super().__str__().replace("\\", "\\\\")


def moveShaders(targetDirectory: str, sourceDirectory: str) -> None:
    if not os.path.isdir(targetDirectory):
        os.mkdir(targetDirectory)

    for file in os.scandir(sourceDirectory):
        shutil.copyfile(file, f"{targetDirectory}\\{file.name}")


def createConfig(targetPath: str) -> None:
    src = "{\n\t\"appliedShaders\" : {\n\t\t\"vertex\" : ["

    shadersDir = "../ruby/src/render/shaders/list/"
    vetexList = utility.findRecursive(shadersDir, "Vertex.*", ["glsl"])

    basePath = pathlib.Path("..\\ruby\src\\render\\shaders\\list")
    for (i, path) in vetexList:
        path = __getRelativePath(path, basePath)
        
        src += path + "\", "
    else:
        src = src[:-2] + "],\n\t\t\"fragment\" : ["

    fragmentList = utility.findRecursive(shadersDir, "Fragment.glsl", ["glsl"])
    for (i, path) in fragmentList:
        path = __getRelativePath(path, basePath)
        
        src += path + "\", "

    src = src[:-2] + "]\n\t}\n}"

    with open(targetPath, "w") as file:
        file.write(src)

# private

def __getRelativePath(path: pathlib.WindowsPath, basePath: pathlib.Path) -> str:
    path = path.relative_to(basePath).__str__()
    path = "shaders\\" + path
    path.replace("\\", "\\\\")

    return "\"" + path

