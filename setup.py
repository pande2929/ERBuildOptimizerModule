from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup
import pybind11

#cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']

bo_module = Pybind11Extension(
    'ERBuildOptimizerModule',
    sources=['cpp/module.cpp', "cpp/ERBuildOptimizer.cpp", "cpp/SubsetSum.cpp"],
    include_dirs=[pybind11.get_include()],
    language='c++',
    #extra_compile_args=cpp_args,
    )

setup(
    name='ERBuildOptimizerModule',
    version='0.8.1',
    author="Morgan Scales",
    author_email="morganscales118@gmail.com",
    description='Build optimization backend functionality.',
    ext_modules=[bo_module],
    zip_safe=False,
    python_requires=">=3.6",
)