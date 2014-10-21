CMWC = -lCMWC -I./CMWC/inc
eSDL = -leSDL -I./eSDL/inc -I./SDL2/inc
LIBS = -mwindows -L./bin $(CMWC) $(eSDL)
CXX = g++
CXXFLAGS = -Ofast -Wall -std=c++1y -I./inc
NAME = Game

all:
	busybox rm -rf bin
	mkdir bin
	$(MAKE) -C eSDL/
	busybox cp -a eSDL/bin/. bin/
	busybox cp -a SDL2/bin/. bin/
	$(MAKE) -C CMWC/
	busybox cp -a CMWC/bin/. bin/
	cd bin
	busybox cp -a res/. bin/$(NAME)
	$(CXX) $(CXXFLAGS) src/*.cpp -o bin/$(NAME).exe $(LIBS)
