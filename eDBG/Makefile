CXXFLAGS += -fpic -shared
LIB = $(PRE)eDBG$(DLL)

all:
	$(DEL) bin
	mkdir bin
	$(CXX) $(CXXFLAGS) src/*.cpp -o bin/$(LIB)
