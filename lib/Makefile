export CXXFLAGS += -fpic -shared

each/%:
	-$(MAKE) -C $* MODULE=$* || $(CXX) $(CXXFLAGS) -I$*/inc $*/src/*.cpp -o $(ROOT)$*$(DLL)
	$(COPY) $*$(SEP)LICENSES $(subst /,\\,$(ROOT))
all:
	$(MAKE) $(foreach llib, $(filter %/, $(wildcard lib*/)), each/$(patsubst %/,%,$(llib)))
