NAME = WAM
ifeq ($(OS),Windows_NT)
export WINDOWS = 1
endif
release: CXXFLAGS = -DNDEBUG=1
LDFLAGS += -Wl,-rpath,'$$ORIGIN' $(if $(WINDOWS),-mwindows,)
export CXX = clang++
export CXXFLAGS = -Ofast -Wall -fno-exceptions -std=c++1y -Iinc/
export DLL = $(if $(WINDOWS),.dll,.so)
export COPY = $(if $(WINDOWS),@-xcopy /y /q /s /e,@-cp -a)
export SEP = $(if $(WINDOWS),\\,/)
export ROOT = $(CURDIR)/bin/
EXT = $(if $(WINDOWS),.exe,.elf)
SDL2 = -lSDL2 -lSDL2_ttf -lSDL2_image
release:
	@$(MAKE) all
all:
	@-mkdir bin
	@-mkdir bin$(SEP)$(NAME)
	$(COPY) res$(SEP). bin$(SEP)$(NAME)
	$(MAKE) -C lib
	$(CXX) $(CXXFLAGS) $(SDL2) $(LDFLAGS) src/*.cc -o bin/$(NAME)$(EXT) -Ilib/libeK/SDL2/inc -Lbin $(foreach llib, $(filter %/, $(wildcard lib/lib*/)), -l$(patsubst lib/lib%/,%,$(llib)) -I$(llib)inc)
