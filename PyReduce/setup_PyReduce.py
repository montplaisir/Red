from distutils.core import setup, Extension
from Cython.Build import cythonize

import os
import sys

# This value should be set when calling the script
use_openmp = 1

# Hardcoding path to Reduce
red_path="../src/"

os_include_dirs = [red_path]

compile_args = []
compile_args.append("-std=c++14")
compile_args.append("-Wall")
compile_args.append("-Wextra")
compile_args.append("-pthread")
link_args = []
link_args.append(red_path + "libRed.so")

if (use_openmp):
    compile_args.append("-fopenmp")
    link_args.append("-fopenmp")

# Look for librairies in Nomad distribution
if sys.platform.startswith("linux"):
    link_args.append("-Wl,-rpath," + red_path)

setup(
    ext_modules = cythonize(Extension(
           "PyReduce", # extension name
           sources = ["PyReduce.pyx", "reduceCyInterface.cpp"], # Cython source and interface
           include_dirs = os_include_dirs,
           extra_compile_args = compile_args,
           extra_link_args = link_args,
           language = "c++"
           ))
)

