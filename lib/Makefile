export CXXFLAGS += -fpic -shared

each/%:
	if ! $(MAKE) -C $* MODULE=$* ; then $(CXX) $(CXXFLAGS) -I$*/inc $*/src/*.cpp -o $(ROOT)$*$(DLL); fi
	$(COPY) $*$(SEP)LICENSES $(ROOT)
all:
	make $(foreach llib, $(filter %/, $(wildcard lib*/)), each/$(patsubst %/,%,$(llib)))