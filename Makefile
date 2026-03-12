# OS Detection
ifeq ($(OS),Windows_NT)
    DETECTED_OS := windows
else
    DETECTED_OS := $(shell uname -s 2>/dev/null || echo unknown)
endif

# Shared library extension and flags by OS
ifeq ($(DETECTED_OS),Darwin)
    SHARED_EXT := dylib
    LDFLAGS := -dynamiclib -fPIC
else ifneq ($(filter Linux FreeBSD OpenBSD NetBSD,$(DETECTED_OS)),)
    SHARED_EXT := so
    LDFLAGS := -shared -fPIC
else
    SHARED_EXT := so
    LDFLAGS := -shared -fPIC
endif

# Directories
SOURCE_DIR   := source
INCLUDE_DIR   := include
BUILD_DIR := .build

# Compiler and tools
CC      := gcc
AR      := ar
CFLAGS  := -I${INCLUDE_DIR} -Wall -Wextra -Werror -g3

# Library names
STATIC_LIB := $(BUILD_DIR)/libcgeneric.a
SHARED_LIB := $(BUILD_DIR)/libcgeneric.$(SHARED_EXT)

# Source & object files
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# One library per source file
STATIC_LIBS := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/lib%.a,$(SOURCES))
SHARED_LIBS := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/lib%.$(SHARED_EXT),$(SOURCES))

# Default target
all: $(STATIC_LIB) $(SHARED_LIB) ${STATIC_LIBS} ${SHARED_LIBS}

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile .c -> .o into .build
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Static library (.a)
$(STATIC_LIB): $(OBJECTS)
	$(AR) rcs $@ $^

# Shared library (.so)
$(SHARED_LIB): $(OBJECTS)
	$(CC) ${LDFLAGS} -o $@ $^

# Create one archive per object
$(BUILD_DIR)/lib%.a: $(BUILD_DIR)/%.o
	$(AR) rcs $@ $<

# Create one shared object per object
$(BUILD_DIR)/lib%.$(SHARED_EXT): $(BUILD_DIR)/%.o
	$(CC) $(LDFLAGS) -fPIC -o $@ $<

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
