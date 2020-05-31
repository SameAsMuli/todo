CLR_COMP:=`tput setaf 6`
CLR_CONFIG:=`tput setaf 5`
CLR_END:=`tput sgr0`
CLR_INFO:=`tput setaf 4`
CLR_LINK:=$(CLR_COMP)`tput bold`

BDIR:=bin
ODIR:=obj
SDIR:=src

BUILD_DIRS:=$(BDIR) $(ODIR)

TARGET:=$(BDIR)/todo

CPP_FLAGS:=-std=c++17 -g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

COMPONENTS:= \
  HelpFunction \
  InputParser \
  TodoFunction

OBJS:=$(patsubst %,$(ODIR)/%.o,$(COMPONENTS))

$(TARGET): $(SDIR)/main.cpp $(OBJS) | $(BDIR)
	@echo "$(CLR_LINK)Linking binary $(@F) ...$(CLR_END)"
	@$(CXX) $(CPP_FLAGS) -o $@ $^

$(ODIR)/%.o: $(SDIR)/%.cpp $(SDIR)/%.hpp | $(ODIR)
	@echo "$(CLR_COMP)Compiling object $(@F) ...$(CLR_END)"
	@$(CXX) -c $(CPP_FLAGS) -o $@ $<

$(BUILD_DIRS):
	@echo "$(CLR_CONFIG)Creating '$@' directory$(CLR_END)"
	@mkdir -p $@

.PHONY: clean
clean:
	@echo "$(CLR_INFO)Deleting build objects ...$(CLR_END)"
	@rm -f $(TARGET) $(OBJS)
