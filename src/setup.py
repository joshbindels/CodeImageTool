import sys
from cx_Freeze import setup, Executable

application_title = "test"
main_python_file="main.py"
base=None

includes={"PIL", "constants", "ImageHandler"}

setup(
    name=application_title,
    version="0.1",
    description="app",
    options={"build_exe": {"includes":includes}},
    executables=[Executable(main_python_file, base=base)]
)
