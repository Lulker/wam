CXXFLAGS += -ISDL2/inc -lSDL2 -lSDL2_ttf -lSDL2_image $(if $(filter $(OS),WINDOWS_NT),-LSDL2/$(PROCESSOR_ARCHITECTURE),)

all:
	$(CXX) $(CXXFLAGS) src/*.cpp -o $(ROOT)$(MODULE)$(DLL)
	$(if $(filter $(OS),WINDOWS_NT),$(COPY) SDL2/$(PROCESSOR_ARCHITECTURE)/* $(ROOT),)
