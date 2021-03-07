.DEFAULT: all
all:
	@$(MAKE) -j -C build

.PHONY: test
test:
	@$(MAKE) -j -C build test

%:
	@$(MAKE) -j -C build $(MAKECMDGOALS)
