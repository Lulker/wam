NAME = WAM
debug: CXXFLAGS = -DeDBG_ON=1 -DGLIBCXX_FORCE_NEW=1
debug: LDFLAGS = $(if $(filter-out $(OS),WINDOWS_NT),-mconsole,)
LDFLAGS += -Wl,-rpath,'$$ORIGIN' $(if $(filter-out $(OS),WINDOWS_NT),-mwindows,)
export CXX = g++
export CXXFLAGS = -Ofast -Wall -fno-exceptions -std=c++1y -Iinc/
export DLL = $(if $(filter-out $(OS),WINDOWS_NT),.dll,.so)
export COPY = $(if $(filter-out $(OS),WINDOWS_NT),-xcopy /y /s /e,-cp -a)
export SEP = $(if $(filter-out $(OS),WINDOWS_NT),\\,/)
export ROOT = $(CURDIR)/bin/
EXT = $(if $(filter-out $(OS),WINDOWS_NT),.exe,.elf)

debug:
	$(MAKE) all
all:
	-mkdir bin
	-mkdir bin$(SEP)$(NAME)
	$(COPY) res$(SEP). bin$(SEP)$(NAME)
	$(MAKE) -C lib
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/*.cpp -o bin/$(NAME)$(EXT) -Ilib/libeK/SDL2/inc -Lbin $(foreach llib, $(filter %/, $(wildcard lib/lib*/)), -l$(patsubst lib/lib%/,%,$(llib)) -I$(llib)inc)
