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
