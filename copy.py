import sys
from distutils.dir_util import copy_tree

copy_tree(sys.argv[1], sys.argv[2])
