export CXXFLAGS += -fpic -shared

each/%:
	-$(MAKE) -C $* MODULE=$* || $(CXX) $(CXXFLAGS) -I$*/inc $*/src/*.cc -o $(ROOT)$*$(DLL)
	$(COPY) $*$(SEP)LICENSES $(if $(WINDOWS),$(subst /,\\,$(ROOT)),$(ROOT))
all:
	$(MAKE) $(foreach llib, $(filter %/, $(wildcard lib*/)), each/$(patsubst %/,%,$(llib)))
