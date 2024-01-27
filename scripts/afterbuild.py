import utility

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

    shaders_dir = "../ruby/src/render/shaders/list/"

    # list of vertex shaders
    vertex_list = utility.findRecursive(shaders_dir, "Vertex.*", ["glsl"])

    base_path = pathlib.Path("..\\ruby\src\\render\\shaders\\list")
    for (i, path) in vertex_list:
        path = __get_relative_path(path, base_path)
        
        src += path + "\", "
    else:
        src = src[:-2] + "],\n\t\t\"fragment\" : ["

    # list of fragment shaders
    fragment_list = utility.findRecursive(shaders_dir, "Fragment.glsl", ["glsl"])
    for (i, path) in fragment_list:
        path = __get_relative_path(path, base_path)
        
        src += path + "\", "

    src = src[:-2] + "]\n\t}\n}"

    with open(target_path, "w") as file:
        file.write(src)


def __get_relative_path(path: pathlib.WindowsPath, base_path: pathlib.Path) -> str:
    path = path.relative_to(base_path).__str__()
    path = "shaders\\" + path
    path.replace("\\", "\\\\")

    return "\"" + path

