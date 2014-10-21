SDL2 += -lSDL2 -lSDL2_ttf -lSDL2_image -I../SDL2/inc
CXXFLAGS += -fpic -shared
LIB = $(PRE)eK$(DLL)
all:
	$(DEL) bin
	mkdir bin
	$(CXX) $(CXXFLAGS) src/*.cpp -o bin/$(LIB) $(SDL2)
