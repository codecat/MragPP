Mrag++
======

Mrag++ is a C++ library for game development in SDL2. Its structure is loosely based on the concept of XNA (or Monogame).

Dependencies
============

The following dependencies are required for Mrag++ to build:

* [Cmake](http://www.cmake.org/)
* [SDL2.0](http://libsdl.org/download-2.0.php)
* libScratch (comes shipped)

Building
========

To build Mrag++, do the following:

    mkdir build
    cd build
    cmake ..

Or, for Windows (Visual Studio):

    mkdir visualstudio
    cd visualstudio
    cmake -G "Visual Studio 10 2010" ..

This will build a static library to build against as `libMragpp.a`, `libMragpp.dylib` or `libMragpp.lib`, depending on your platform.

License
=======

Mrag++ is licensed under the permissive [MIT license](LICENSE).
