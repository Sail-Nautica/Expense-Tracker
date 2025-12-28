# Compiler and flags
CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
CPPFLAGS ?=
LDFLAGS ?=

# Target and directories
TARGET ?= expense-tracker
SRC := $(wildcard src/*.cpp)
BUILD_DIR := build
BIN_DIR := bin

# Derived paths
OBJ := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
BIN := $(BIN_DIR)/$(TARGET)

.PHONY: all run clean

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

run: $(BIN)
	@echo Running $(BIN)...
	@$(BIN)

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
