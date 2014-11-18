War Among Minds
===============

TODO Description

* [Mingw-dist](http://nuwen.net/mingw.html)
* [Tiled](http://www.mapeditor.org/)

#Coding Standard

* Class implementation is separated in header(with all methods that could be inlined) and files
* Methods and Attributes are lowercase, using underscore separation whenever needed
* K&R Style indentation where braces are omitted whenever possible
* Function definition does not end with ;
* Oneliner functions should be packed
* Classes use PascalCase

#Compile instructions

* make and g++ or clang++ with c++1y support are required
* Run vcmake.cmd  to compile with Visual Express 2013 (Visual Studio 12.0)
* Vector math requires a computer with at least SSE2 (SSE4.1 if possible)

```
  git clone https://github.com/Lulker/wam.git
  cd wam
  make release
```
