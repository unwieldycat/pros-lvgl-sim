# Script to list files in a directory for CMakeLists.txt sources
# because glob is bad!!!

from argparse import ArgumentParser
from common.logger import error, warn, step
from pathlib import Path


def get_sources(path):
    path = Path(path)
    sim_sources = list(path.rglob("**/*"))
    rel_paths = []
    for source in sim_sources:
        if not source.is_file():
            continue
        rel_paths.append(source.relative_to(path.parent).as_posix())
    rel_paths = sorted(rel_paths)
    return "\n".join(rel_paths)


def main():
    parser = ArgumentParser(
        prog="list_sources.py",
        description="A cross-platform script to list sources for CMakeLists.txt file",
    )
    parser.add_argument(
        "source_dir",
        type=str,
        help="Source directory",
    )
    args = parser.parse_args()

    path = Path(args.source_dir)
    if not path.exists():
        return
    elif not path.is_dir():
        return

    print(get_sources(args.source_dir))


if __name__ == "__main__":
    main()
