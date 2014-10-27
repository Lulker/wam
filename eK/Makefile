SDL2 += -lSDL2 -lSDL2_ttf -lSDL2_image -I../SDL2/inc
CXXFLAGS += -fpic -shared
LIB = $(PRE)eK$(DLL)

all:
	$(CXX) $(CXXFLAGS) $(eDBG) src/*.cpp -o bin/$(LIB) $(SDL2)
