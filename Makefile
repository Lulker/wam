NAME = WAM
CXX = g++
CMWC = -lCMWC -I./CMWC/inc
eK = -leK -I./eK/inc -I./SDL2/inc
LIBS = -L./bin $(CMWC) $(eK)
CXXFLAGS = -Ofast -Wall -std=c++1y -I./inc
LDFLAGS = -Wl,-rpath,'$$ORIGIN'

ifeq ($(OS),Windows_NT)
	EXT = .exe
	DLL = .dll
	DEL = -rd /s /q
	COPY = xcopy /e
	LIBS += -mwindows
	SEP = \\
	export SDL2 = -L../SDL2/$(PROCESSOR_ARCHITECTURE)
else
	SEP = /
	EXT = .elf
	PRE = lib
	DLL = .so
	DEL = -rm -rf
	COPY = cp -a
endif

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
	mkdir bin\\WAM
	$(MAKE) -C eK
	$(COPY) eK$(SEP)bin$(SEP). bin$(SEP)
	$(COPY) SDL2$(SEP)$(PROCESSOR_ARCHITECTURE)$(SEP). bin$(SEP)
	$(MAKE) -C CMWC
	$(COPY) CMWC$(SEP)bin$(SEP). bin$(SEP)
	cd bin
	$(COPY) res$(SEP). bin$(SEP)$(NAME)
	$(COPY) LICENSES$(SEP). bin
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/*.cpp -o bin/$(NAME)$(EXT) $(LIBS)
