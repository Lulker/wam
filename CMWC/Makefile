CXXFLAGS = -Ofast -fpic -shared -Wall -std=c++1y -I./inc
LIB = $(PRE)CMWC$(DLL)

all:
	$(DEL) bin
	mkdir bin
	$(CXX) $(CXXFLAGS) src/*.cpp -o bin/$(LIB)
