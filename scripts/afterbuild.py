import utility
from utility import ROOT_FOLDER 

import shutil
import pathlib
import os


def move_shaders(target_dir: str, source_dir: str) -> None:
    if not os.path.isdir(target_dir):
        os.mkdir(target_dir)

    for file in os.scandir(source_dir):
        shutil.copyfile(file, f"{target_dir}\\{file.name}")


def create_config(target_path: str) -> None:
    src = "{\n\t\"appliedShaders\" : {\n\t\t\"vertex\" : ["

    shaders_dir = pathlib.Path(
        str(ROOT_FOLDER) + "\\resources\\shaders")

    # list of vertex shaders
    vertex_list = utility.find_recursive(str(shaders_dir), "Vertex.*", ["glsl"])

    for (i, path) in vertex_list:
        path = __get_relative_path(path, shaders_dir)
        
        src += path + "\", "
    else:
        src = src[:-2] + "],\n\t\t\"fragment\" : ["

    # list of fragment shaders
    fragment_list = utility.find_recursive(str(shaders_dir), "Fragment.glsl", ["glsl"])
    for (i, path) in fragment_list:
        path = __get_relative_path(path, shaders_dir)
        
        src += path + "\", "

    src = src[:-2] + "]\n\t}\n}"

    with open(target_path, "w") as file:
        file.write(src)

    return src


def __get_relative_path(path: pathlib.WindowsPath, base_path: pathlib.Path) -> str:
    path = str(path.relative_to(base_path))
    print(f"before: {path}")
    path = path.replace("\\", "\\\\")
    print(f"after: {path}")
    path = "shaders\\\\" + path

    return "\"" + path
