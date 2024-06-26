# Script to update liblvgl and fix include directives

from os import chmod
from pathlib import Path
import re
import shutil
import stat
import subprocess

# Logging

WARN_COLOR = "\033[1;33m"
ERR_COLOR = "\033[0;31m"
STEP_COLOR = "\033[1;37m"
MSG_COLOR = "\033[0;37m"
NO_COLOR = "\033[0m"


def warn(message):
    print(f"{WARN_COLOR}WARNING: {MSG_COLOR}{message}{NO_COLOR}")


def error(message):
    print(f"{ERR_COLOR}ERROR: {MSG_COLOR}{message}{NO_COLOR}")


def step(message):
    print(f"{STEP_COLOR}- {message} -{NO_COLOR}")


# Utility


def onexc_chmod(retry, path, err):
    chmod(path, stat.S_IWUSR)
    try:
        retry(path)
    except Exception as err:
        error(f"Failed to rmtree with exception: {err}")


def clone():
    if Path("liblvgl/").exists():
        shutil.rmtree("liblvgl/", onexc=onexc_chmod)

    sub_proc = subprocess.Popen(
        f"git clone -b master https://github.com/purduesigbots/liblvgl.git --recursive",
        shell=True,
    )
    if sub_proc.wait() != 0:
        error("Clone failed, exiting...")
        exit(1)


def fix_includes(file_path):
    def resolve_rel_include(match):
        file = Path(file_path)
        include_path = match.group(1)

        parent_dir = file.parent.relative_to("simulator")

        if parent_dir.is_relative_to("src/"):
            parent_dir = parent_dir.relative_to("src/")
        elif parent_dir.is_relative_to("include/"):
            parent_dir = parent_dir.relative_to("include/")

        new_include = parent_dir.joinpath(include_path).as_posix()
        return f'#include "{new_include}"'

    with open(file_path, "r", encoding="utf-8") as file:
        data = file.read()
        data = re.sub(r'#include "(lv_.*\.h)"', resolve_rel_include, data)

    with open(file_path, "w", encoding="utf-8") as file:
        file.write(data)


# Main


def main():
    warn("This script is destructive and will remove all liblvgl files!")
    input("Press any key to continue...")

    step("Clone liblvgl")
    clone()

    step("Replace liblvgl files")
    shutil.rmtree("simulator/src/liblvgl/", ignore_errors=True)
    shutil.rmtree("simulator/include/liblvgl/", ignore_errors=True)
    shutil.copytree("liblvgl/src/liblvgl", "simulator/src/liblvgl")
    shutil.copytree("liblvgl/include/liblvgl", "simulator/include/liblvgl")
    Path("simulator/src/liblvgl/display.c").unlink(True)

    step("Fix relative includes")
    for path in Path("simulator/src/liblvgl").rglob("**/*.c"):
        fix_includes(path)

    for path in Path("simulator/include/liblvgl").rglob("**/*.h"):
        fix_includes(path)

    step("Success")


if __name__ == "__main__":
    main()
