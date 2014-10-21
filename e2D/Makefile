SDL2 = -L../SDL2/lib -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -I../SDL2/inc
LIBS = $(SDL2)
CXX = g++
CXXFLAGS = -Ofast -fpic -shared -Wall -std=c++1y -I./inc
DLL = e2D.dll

all:
	$(CXX) $(CXXFLAGS) src/*.cpp -o bin/$(DLL) $(LIBS)
