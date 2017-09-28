

<img align="right" src="ale.gif" width=50>


Windows wrappers for the [Arcade Learning Environment](https://github.com/mgbellemare/Arcade-Learning-Environment/)/Xitari. 
============

xitari-Windows are bindings to Deepmind´s xitari, published here:

https://github.com/deepmind/xitari.git

This repository currently builds a strongly-typed .NET API for use from C# and/or F#. The API binding is currently being tested and functionality will be added to facilitate the use of Windows-based deep learning frameworks. 

### Dependencies

- An environmental variable named SWIG_PATH pointing to [Simplified Wrapper and Interface Generator](http://www.swig.org) executable (.exe) file. This repo has been tested with Swig 3.0.10, available from [here](https://sourceforge.net/projects/swig/files/swigwin/)

- VS 2017, including "Desktop development with C++" & ".Net desktop development". This repo has been tested with Visual Studio Community 2017 Version 15.3.2 and 15.3.3

### TODO

- Finalize the .NET API
- Create a cleaner C++ API as [here](https://github.com/facebookresearch/ELF/blob/master/atari/atari_game.h)
- Review if Rcpp could be leveraged (R-Binding) 




