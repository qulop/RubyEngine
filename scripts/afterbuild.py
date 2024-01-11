import shutil
import os


def moveShaders(targetDirectory: str, sourceDirectory: str):
    if not os.path.isdir(targetDirectory):
        os.mkdir(targetDirectory)

    for file in os.scandir(sourceDirectory):
        shutil.copyfile(file, f"{targetDirectory}\\{file.name}")