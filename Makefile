CLR_COMP:=`tput setaf 6`
CLR_CONFIG:=`tput setaf 5`
CLR_END:=`tput sgr0`
CLR_INFO:=`tput setaf 4`
CLR_LINK:=$(CLR_COMP)`tput bold`

BIN:=bin
OBJ:=obj
SRC:=src

# Allow Clang Complete to use the build if specified
ifneq ("$(wildcard $(CLANG_COMPLETE_CC_ARGS))","")
  CXX:=$(CLANG_COMPLETE_CC_ARGS) $(CXX)
endif

# Use ccache (if available) for faster compilation
ifneq ($(shell which ccache 2> /dev/null),)
  CXX:=ccache $(CXX)
endif

CPP_FLAGS:= \
  -std=c++17 -g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual \
  -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self \
  -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual \
  -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
  -Wstrict-overflow=5 -Wundef -Wswitch-default -Werror -Wno-unused

COMP_OPTIONS:=$(CPP_FLAGS) -I $(SRC)

BUILD_DIRS:=$(BIN) $(OBJ)

SRC_SUB_DIRS:= \
  action \
  env \
  task \
  todo \
  util

TARGET:=$(BIN)/todo

OBJS:= \
  $(foreach DIR, $(SRC_SUB_DIRS), \
    $(patsubst %, $(OBJ)/$(DIR)/%.o, \
      $(basename $(notdir $(wildcard $(SRC)/$(DIR)/*.cpp))) \
     ) \
   )

define genRules
$(OBJ)/$(1): | $(OBJ)
	@mkdir -p $(OBJ)/$(1)

$(OBJ)/$(1)/%.o: $(SRC)/$(1)/%.cpp $(SRC)/$(1)/%.hpp | $(OBJ)/$(1)
	@echo "$(CLR_COMP)Compiling $(1)/$$(basename $$(@F))...$(CLR_END)"
	@$(CXX) -c $(COMP_OPTIONS) -o $$@ $$<
endef

$(TARGET): $(SRC)/main.cpp $(OBJS) | $(BIN)
	@echo "$(CLR_LINK)Linking binary $(@F)...$(CLR_END)"
	@$(CXX) $(COMP_OPTIONS) -o $@ $^

$(foreach DIR, $(SRC_SUB_DIRS), $(eval $(call genRules,$(DIR))))

$(BUILD_DIRS):
	@echo "$(CLR_CONFIG)Creating '$@' directory$(CLR_END)"
	@mkdir -p $@

.PHONY: clean
clean:
	@echo "$(CLR_INFO)Deleting build objects ...$(CLR_END)"
	@rm -rf $(BIN)/* $(OBJ)/*
