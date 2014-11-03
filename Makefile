NAME = WAM
LDFLAGS = -Wl,-rpath,'$$ORIGIN' $(if $(filter $(OS),WINDOWS_NT),-mwindows -e _mainCRTStartup,)
debug: CXXFLAGS = -DeDBG_ON=1 -DGLIBCXX_FORCE_NEW=1
export CXX = g++
export CXXFLAGS = -Ofast -Wall -fno-exceptions -std=c++1y -Iinc/
export DLL = $(if $(filter $(OS),WINDOWS_NT),.dll,.so)
export COPY = $(if $(filter $(OS),WINDOWS_NT),-xcopy /y /s /e,-cp -a)
export SEP = $(if $(filter $(OS),WINDOWS_NT),\\,/)
export ROOT = $(CURDIR)$(SEP)bin$(SEP)
EXT = $(if $(filter $(OS),WINDOWS_NT),.exe,.elf)

debug:
	make all
all:
	-mkdir bin
	-mkdir bin$(SEP)$(NAME)
	$(COPY) res$(SEP). bin$(SEP)$(NAME)
	make -C lib
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/*.cpp -o bin/$(NAME)$(EXT) -Ilib/libeK/SDL2/inc -Lbin $(foreach llib, $(filter %/, $(wildcard lib/lib*/)), -l$(patsubst lib/lib%/,%,$(llib)) -I$(llib)inc)
