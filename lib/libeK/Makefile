CXXFLAGS += $(if $(WINDOWS),-LSDL2/$(PROCESSOR_ARCHITECTURE),) -ISDL2/inc -lSDL2 -lSDL2_ttf -lSDL2_image

all:
	$(CXX) $(CXXFLAGS) src/*.cpp -o $(ROOT)$(MODULE)$(DLL)
	$(if $(WINDOWS),$(COPY) SDL2\\$(PROCESSOR_ARCHITECTURE)\\. $(subst /,\\,$(ROOT)),)
