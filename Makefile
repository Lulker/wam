NAME = WAM
ifeq ($(OS),Windows_NT)
export WINDOWS = 1
endif
release: CXXFLAGS = -DNDEBUG=1
LDFLAGS += -Wl,-rpath,'$$ORIGIN'
export CXX = clang++
export CXXFLAGS += -Ofast -march=native -Wall -fno-exceptions -std=c++1y -Iinc/
export DLL = $(if $(WINDOWS),.dll,.so)
export COPY = $(if $(WINDOWS),@-xcopy /y /q /s /e,@-cp -a)
export SEP = $(if $(WINDOWS),\\,/)
export ROOT = $(CURDIR)/bin/
SGE = SGE/src/*.cc -ISGE/inc $(if $(WINDOWS),-LSDL2/$(PROCESSOR_ARCHITECTURE) -lws2_32,) -lSDL2 -lSDL2_ttf -lSDL2_image
all:
	@-mkdir bin
	@-mkdir bin$(SEP)$(NAME)
	$(COPY) res$(SEP). bin$(SEP)$(NAME)
	$(if $(WINDOWS),$(COPY) SDL2\\$(PROCESSOR_ARCHITECTURE)\\*.dll $(subst /,\\,$(ROOT)),)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/*.cc -o bin/$(NAME)$(if $(WINDOWS),.exe,.elf) -Lbin $(SGE) -lpthread $(foreach llib, $(filter %/, $(wildcard lib/lib*/)), -l$(patsubst lib/lib%/,%,$(llib)) -I$(llib)inc)
release:
	@$(MAKE) all
