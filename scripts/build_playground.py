import utility
from utility import CALL_DIR, ROOT_FOLDER, ENGINE_NAME, PLAYGROUND_NAME

import os


class Builder:
    def __init__(self):
        self.__is_engine_build_required = True
        self.__engine_location = None
        self.__pg_location = None

        self.__check_engine_for_assembled()

    def build_engine(self, config_cmake_cmd: str, build_cmake_cmd: str) -> int:
        if not self.__is_engine_build_required:
            return 0

        os.chdir(str(ROOT_FOLDER))
        utility.go_to_build_directory()
        engine_name = ENGINE_NAME.get()

        if utility.execute(config_cmake_cmd, build_cmake_cmd) != 0:
            return -1

        search_extensions = ["dll", "lib"]
        pattern = f"{engine_name}.*"
        path = f"{ROOT_FOLDER.get()}\\build"
        self.__engine_location = utility.find_recursive(path, pattern, search_extensions)[0][1].parent

        print(f"\n\n\n\n=== Engine build complete ===\n=== Location: {self.__engine_location} ===\n\n\n")

        os.chdir(str(CALL_DIR))

        return 0

    def build_playground(self, config_cmake_cmd: str, build_cmake_cmd: str) -> int:
        pg_root_dir = f"{str(ROOT_FOLDER)}\\playground"

        if self.__is_engine_build_required:
            # Moving engine files(shared and static libraries) to playground directory
            for ext in [".dll", ".lib"]:
                filename = str(ENGINE_NAME) + ext

                utility.move_file_to(filename, self.__engine_location, pg_root_dir)

        os.chdir(f"{str(ROOT_FOLDER)}\\playground")
        utility.go_to_build_directory()

        if utility.execute(config_cmake_cmd, build_cmake_cmd) != 0:
            return -1

        search_dir = f"{str(ROOT_FOLDER)}\\playground\\build"
        pattern = "RubyDemo.exe"
        extensions = ["exe"]

        # Expending in [(fileName, path)] -> (fileName, path) -> path -> path.parent
        #                                          [0]           [1]      <...>.parent
        self.__pg_location = utility.find_recursive(search_dir, pattern, extensions)[0][1].parent

        if self.__is_engine_build_required:
            filename = f"{str(ENGINE_NAME)}.dll"

            utility.move_file_to(filename, pg_root_dir, self.__pg_location)

        os.chdir(str(CALL_DIR))

        print(f"\n\n\n\n=== Playground build complete ====\n=== Location: {self.__pg_location} ===\n\n\n")

        return 0

    def __check_engine_for_assembled(self) -> None:
        pg_root_dir = f"{str(ROOT_FOLDER)}\\playground"
        os.chdir(pg_root_dir)

        if not os.path.isdir("build"):
            return

        pattern = f"{str(ENGINE_NAME)}.*"
        extensions = ["dll", "lib"]

        if not utility.find_recursive(f"{pg_root_dir}\\build", pattern, extensions):
            return
        self.__is_engine_build_required = False

        print("=== Engine is already assembled ===")

    @staticmethod
    def build_failed():
        print("=== Build failed ===")
        exit(1)


def main() -> None:
    engine_cmake_build = {
        "config_cmd": "..",
        "build_cmd": f"--build . --target {ENGINE_NAME.get()}"
    }

    pg_cmake_build = {
        "config_cmd": "..",
        "build_cmd": f"--build . --target {PLAYGROUND_NAME.get()}"
    }

    builder = Builder()

    engine_build_code = builder.build_engine(engine_cmake_build["config_cmd"], engine_cmake_build["build_cmd"])
    if engine_build_code != 0:
        Builder.build_failed()

    pg_build_code = builder.build_playground(pg_cmake_build["config_cmd"], pg_cmake_build["build_cmd"])
    if pg_build_code != 0:
        Builder.build_failed()


if __name__ == "__main__":
    main()
