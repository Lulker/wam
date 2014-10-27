War Among Minds
===============

War Among Minds is an open-source limited-resources spell-casting moba where everyone is a minion!

* [Mingw-dist](http://nuwen.net/mingw.html)
* [Tiled](http://www.mapeditor.org/)

#Coding Standard

* Class implementation is separated by files, class headers amalgamated if constructed only through parent classes
* Classes start with a lowercase character (for class-type declaration), then PascalCase
* Methods and Attributes are lowercase, using underscore separation whenever needed
* K&R Style indentation where braces are omitted whenever possible

#Compile instructions

* make and g++ or clang++ with c++1y support are required

```
  git clone https://github.com/Lulker/wam.git
  cd wam
  make
```
