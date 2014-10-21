CMWC = -lCMWC -I./CMWC/inc
e2D = -le2D -I./e2D/inc -I./SDL2/inc
LIBS = -mwindows -L./bin $(CMWC) $(e2D)
CXX = g++
CXXFLAGS = -Ofast -Wall -std=c++1y -I./inc
NAME = Game

all:
	busybox rm -rf bin
	mkdir bin
	$(MAKE) -C e2D/
	busybox cp -a e2D/bin/. bin/
	busybox cp -a SDL2/bin/. bin/
	$(MAKE) -C CMWC/
	busybox cp -a CMWC/bin/. bin/
	cd bin
	busybox cp -a res/. bin/$(NAME)
	$(CXX) $(CXXFLAGS) src/*.cpp -o bin/$(NAME).exe $(LIBS)
