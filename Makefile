# Variables
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -O2
LDFLAGS  := 
TARGET   := mgnamecard
SRC_DIR  := src
OBJ_DIR  := obj

# Project Specific
CXXFLAGS += $(shell pkg-config --cflags Magick++)
LDFLAGS  += $(shell pkg-config --libs Magick++)

# Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Main Targets
.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compiler
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Dependencies
-include $(DEPS)

clean:
	@if [ -n "$(OBJ_DIR)" ] && [ "$(OBJ_DIR)" != "/" ]; then \
		rm -rf "$(OBJ_DIR)"; \
	fi
	rm -f "$(TARGET)"

run: all
	./$(TARGET) < input.in
