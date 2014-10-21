NAME = WAM
CMWC = -lCMWC -I./CMWC/inc
eK = -leK -I./eK/inc -I./SDL2/inc
CXX = g++
CXXFLAGS = -Ofast -Wall -std=c++1y -I./inc
LDFLAGS = -Wl,-rpath,'$$ORIGIN'

ifeq ($(OS),Windows_NT)
	EXT = .exe
	DLL = .dll
	DEL = rd /s /q
	COPY = xcopy /e
	SO = -mwindows
else
	EXT = .elf
	PRE = lib
	DLL = .so
	DEL = rm -rf
	COPY = cp -a
endif

LIBS = $(SO) -L./bin $(CMWC) $(eK)

export PRE
export DLL
export DEL
export COPY
export CXX
export CXXFLAGS
export LDFLAGS

all:
	$(DEL) bin
	mkdir bin
	mkdir bin/WAM
	$(MAKE) -C eK/
	$(COPY) eK/bin/. bin/
	$(COPY) SDL2/bin/. bin/
	$(MAKE) -C CMWC/
	$(COPY) CMWC/bin/. bin/
	cd bin
	$(COPY) res/. bin/$(NAME)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/*.cpp -o bin/$(NAME)$(EXT) $(LIBS)
