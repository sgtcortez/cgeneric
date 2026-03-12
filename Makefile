# OS Detection
ifeq ($(OS),Windows_NT)
    DETECTED_OS := windows
else
    DETECTED_OS := $(shell uname -s 2>/dev/null || echo unknown)
endif

# Architecture Detection
ifeq ($(OS),Windows_NT)
    DETECTED_ARCH := $(PROCESSOR_ARCHITECTURE)
else
    DETECTED_ARCH := $(shell uname -m 2>/dev/null || echo unknown)
endif

# Add architecture-specific flags for ARM
ifeq ($(DETECTED_ARCH),aarch64)
    CFLAGS += -march=armv8-a
else ifeq ($(DETECTED_ARCH),arm64)
    CFLAGS += -arch arm64
endif

# Directories
SOURCE_DIR   := source
INCLUDE_DIR   := include
BUILD_DIR := .build

# Compiler and tools
CC      := gcc
AR      := ar
CFLAGS  += -I${INCLUDE_DIR} -Wall -Wextra -Werror -g3

# Library names
STATIC_LIB := $(BUILD_DIR)/libcgeneric.a

# Source & object files
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# One library per source file
STATIC_LIBS := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/lib%.a,$(SOURCES))

# Default target
all: $(STATIC_LIB) ${STATIC_LIBS}

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile .c -> .o into .build
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Static library (.a)
$(STATIC_LIB): $(OBJECTS)
	$(AR) rcs $@ $^

# Create one archive per object
$(BUILD_DIR)/lib%.a: $(BUILD_DIR)/%.o
	$(AR) rcs $@ $<

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
