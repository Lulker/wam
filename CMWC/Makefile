CXXFLAGS += -fpic -shared
LIB = $(PRE)CMWC$(DLL)

all:
	$(DEL) bin
	mkdir bin
	$(CXX) $(CXXFLAGS) src/*.cpp -o bin/$(LIB)
