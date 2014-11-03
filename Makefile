.PHONY: debug release legacy all
debug: CXXFLAGS = -DeDBG_ON=1
debug: eDBG = -L../eDBG/bin -leDBG
legacy: CXXFLAGS = -m32
NAME = WAM
CXX = g++
CMWC = -lCMWC -I./CMWC/inc
eK = -leK -I./eK/inc -I./SDL2/inc
eDBG += -I./eDBG/inc -I../eDBG/inc
LIBS = -L./bin $(CMWC) $(eK) $(eDBG)
CXXFLAGS += -Ofast -Wall -fno-exceptions -std=c++1y -I./inc
LDFLAGS = -Wl,-rpath,'$$ORIGIN'

ifeq ($(OS),Windows_NT)
	EXT = .exe
	DLL = .dll
	DEL = -rd /s /q
	COPY = -xcopy /e
	LIBS += -mwindows
	SEP = \\
	SDL2 = -L../SDL2/$(PROCESSOR_ARCHITECTURE)
	CMD = $(COPY) SDL2$(SEP)$(PROCESSOR_ARCHITECTURE)$(SEP). bin$(SEP)
else
	SEP = /
	EXT = .elf
	PRE = lib
	DLL = .so
	DEL = -rm -rf
	COPY = -cp -a
endif

legacy: SDL2 = -L../SDL2/x86

export PRE
export DLL
export DEL
export COPY
export CXX
export CXXFLAGS
export LDFLAGS
export eDBG
export SDL2

debug:
	$(DEL) bin
	mkdir bin
	$(DEL) eDBG$(SEP)bin
	mkdir eDBG$(SEP)bin
	$(MAKE) -C eDBG
	$(COPY) eDBG$(SEP)bin$(SEP). bin$(SEP)
	make all

legacy:
	make release

release:
	$(DEL) bin
	mkdir bin
	make all

all:
	mkdir bin$(SEP)WAM
	$(DEL) CMWC$(SEP)bin
	mkdir CMWC$(SEP)bin
	$(MAKE) -C CMWC
	$(COPY) CMWC$(SEP)bin$(SEP). bin$(SEP)
	$(DEL) eK$(SEP)bin
	mkdir eK$(SEP)bin
	$(MAKE) -C eK
	$(COPY) eK$(SEP)bin$(SEP). bin$(SEP)
	$(CMD)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/*.cpp -o bin/$(NAME)$(EXT) $(LIBS)
	$(COPY) res$(SEP). bin$(SEP)$(NAME)
	$(COPY) LICENSES$(SEP). bin
