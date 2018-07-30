from distutils.core import setup, Extension
import os.path, sys

ale_c_lib = 'x64/Release/Xitari.Core.CSBinding-0.4.dll'
if not os.path.isfile(ale_c_lib):
  print('ERROR: Unable to find required library: %s. Please ensure you\'ve '\
    'built Xitari using Visual Studio 2017.'%(ale_c_lib))
  sys.exit()

module1 = Extension('xitari_python_interface.xitari_c_wrapper',
                    libraries = ['ale_c'],
                    include_dirs = ['src'],
                    library_dirs = ['ale_python_interface'],
                    extra_compile_args=['-D__STDC_CONSTANT_MACROS', '-std=c++11'],
                    sources=['ale_python_interface/ale_c_wrapper.cpp'])
setup(name = 'ale_python_interface',
      version='0.6',
      description = 'Arcade Learning Environment Python Interface',
      url='https://github.com/bbitmaster/ale_python_interface',
      author='Ben Goodrich',
      license='GPL',
      ext_modules = [module1],
      packages=['ale_python_interface'],
      package_dir={'ale_python_interface': 'ale_python_interface'},
      package_data={'ale_python_interface': ['libale_c.so']})