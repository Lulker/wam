.PHONY: debug release all
debug: CXXFLAGS = -DeDBG_ON=1
debug: eDBG = -L../eDBG/bin -leDBG
NAME = WAM
CXX = g++
CMWC = -lCMWC -I./CMWC/inc
eK = -leK -I./eK/inc -I./SDL2/inc
eDBG += -I./eDBG/inc -I../eDBG/inc
LIBS = -L./bin $(CMWC) $(eK) $(eDBG)
CXXFLAGS += -Ofast -Wall -std=c++1y -I./inc
LDFLAGS = -Wl,-rpath,'$$ORIGIN'

ifeq ($(OS),Windows_NT)
	EXT = .exe
	DLL = .dll
	DEL = -rd /s /q
	COPY = -xcopy /e
	LIBS += -mwindows
	SEP = \\
	export SDL2 = -L../SDL2/$(PROCESSOR_ARCHITECTURE)
else
	SEP = /
	EXT = .elf
	PRE = lib
	DLL = .so
	DEL = -rm -rf
	COPY = -cp -a
endif

export PRE
export DLL
export DEL
export COPY
export CXX
export CXXFLAGS
export LDFLAGS
export eDBG

debug:
	$(DEL) bin
	mkdir bin
	$(DEL) eDBG$(SEP)bin
	mkdir eDBG$(SEP)bin
	$(MAKE) -C eDBG
	$(COPY) EDBG$(SEP)bin$(SEP). bin$(SEP)
	make all

release:
	$(DEL) bin
	mkdir bin
	make all

all:
	mkdir bin\\WAM
	$(DEL) CMWC$(SEP)bin
	mkdir CMWC$(SEP)bin
	$(MAKE) -C CMWC
	$(COPY) CMWC$(SEP)bin$(SEP). bin$(SEP)
	$(DEL) eK$(SEP)bin
	mkdir eK$(SEP)bin
	$(MAKE) -C eK
	$(COPY) eK$(SEP)bin$(SEP). bin$(SEP)
	$(COPY) SDL2$(SEP)$(PROCESSOR_ARCHITECTURE)$(SEP). bin$(SEP)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/*.cpp -o bin/$(NAME)$(EXT) $(LIBS)
	$(COPY) res$(SEP). bin$(SEP)$(NAME)
	$(COPY) LICENSES$(SEP). bin
