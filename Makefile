# ==================================================================================================
# Variables

# C++ compiler name
CXX = g++

# Compiler flags
CFLAGS = -std=c++11 -O2 -g

# Debugger flags
#DFLAGS = -pg

# Warning flags
WFLAGS = -Wall -Wextra

# Source files
SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp')

# Dependency files
DEP_DIR = deps
DEP_FILES = $(SRC:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

# Object files
BUILD_DIR = build
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Dummy warning files
WARNINGS = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.w)

# Executable name
EXEC = approxkLCS

# ==================================================================================================
# Configuration

.PHONY: all release debug

# ==================================================================================================
# Main targets

all: release

debug: DFLAGS += -ggdb
debug: $(EXEC)

release: CFLAGS += #-O3 -DNDEBUG
release: WFLAGS =
release: $(EXEC)

# ==================================================================================================
# Main rules

# Build executable from object files
$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(DFLAGS) $(LFLAGS)

# Build object file from source file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEP_DIR)/%.d
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $< $(CFLAGS) $(DFLAGS) $(WFLAGS)

# Create dependency files
$(DEP_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -MM -MT '$(<:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)' $< -MF $@

# ==================================================================================================
# Warnings target, output all g++ warnings without compiling
warnings: CFLAGS += -fsyntax-only
warnings: $(WARNINGS)

# Output warnings
$(BUILD_DIR)/%.w: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $< $(CFLAGS) $(WFLAGS) 2> $@

# ==================================================================================================
# Clean intermediate files (not final results like executables, documentation, packages,...)
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(DEP_DIR)
	rm -rf *~

# Clean everything
clean-all: clean
	rm -rf $(EXEC)
