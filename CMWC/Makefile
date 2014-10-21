CXX = g++
CXXFLAGS = -Ofast -fpic -shared -Wall -std=c++1y -I./inc
DLL = cmwc.dll

all:
	busybox rm -rf bin
	mkdir bin
	$(CXX) $(CXXFLAGS) src/*.cpp -o bin/$(DLL)
