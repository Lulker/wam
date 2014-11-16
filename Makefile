NAME = WAM
ifeq ($(OS),Windows_NT)
export WINDOWS = 1
endif
release: CXXFLAGS = -DNDEBUG=1
LDFLAGS += -Wl,-rpath,'$$ORIGIN' $(if $(WINDOWS),-mwindows,)
export CXX = g++
export CXXFLAGS += -Ofast -march=native -Wall -fno-exceptions -std=c++1y -Iinc/
export DLL = $(if $(WINDOWS),.dll,.so)
export COPY = $(if $(WINDOWS),@-xcopy /y /q /s /e,@-cp -a)
export SEP = $(if $(WINDOWS),\\,/)
export ROOT = $(CURDIR)/bin/
EXT = $(if $(WINDOWS),.exe,.elf)
SGE += -ISGE/inc $(if $(WINDOWS),-LSDL2/$(PROCESSOR_ARCHITECTURE) -lws2_32,) -lSDL2 -lSDL2_ttf -lSDL2_image SGE/src/*.cc
release:
	@$(MAKE) all
all:
	@-mkdir bin
	@-mkdir bin$(SEP)$(NAME)
	$(COPY) res$(SEP). bin$(SEP)$(NAME)
	$(if $(WINDOWS),$(COPY) SDL2\\$(PROCESSOR_ARCHITECTURE)\\. $(subst /,\\,$(ROOT)),)
	$(CXX) $(CXXFLAGS) $(SGE) $(LDFLAGS) src/*.cc -o bin/$(NAME)$(EXT) -Lbin $(foreach llib, $(filter %/, $(wildcard lib/lib*/)), -l$(patsubst lib/lib%/,%,$(llib)) -I$(llib)inc)
