DEBUG_DIR := build
RELEASE_DIR := build/release

.DEFAULT: debug
.PHONY: debug
debug: $(DEBUG_DIR)/Makefile
	@$(MAKE) -j -C $(DEBUG_DIR)

.PHONY: release
release: $(RELEASE_DIR)/Makefile
	@$(MAKE) -j -C $(RELEASE_DIR)

.PHONY: install
install: $(RELEASE_DIR)/Makefile
	@$(MAKE) -j -C $(RELEASE_DIR) install

$(DEBUG_DIR)/Makefile: | $(DEBUG_DIR)
	@cmake -S . -B $(DEBUG_DIR) -D CMAKE_BUILD_TYPE=Debug

$(RELEASE_DIR)/Makefile: | $(RELEASE_DIR)
	@cmake -S . -B $(RELEASE_DIR) -D CMAKE_BUILD_TYPE=Release

$(DEBUG_DIR):
	@mkdir -p $(DEBUG_DIR)

$(RELEASE_DIR):
	@mkdir -p $(RELEASE_DIR)

.PHONY: clean
clean: $(DEBUG_DIR)/Makefile
	@$(MAKE) -j -C $(DEBUG_DIR) clean

.PHONY: cmakeclean
cmakeclean:
	@rm -rf $(RELEASE_DIR)
	@rm -rf $(DEBUG_DIR)

.PHONY: fresh
fresh: cmakeclean
	@$(MAKE)

.PHONY: test
test: $(DEBUG_DIR)/Makefile
	@$(MAKE) -j -C $(DEBUG_DIR) test
