import sys
import shutil

shutil.copytree(sys.argv[1], sys.argv[2], dirs_exist_ok=True)
