CC = gcc
CFLAGS = -Wall -Wextra
BUILD_DIR = build

# Source files
SRCS = main.c bmp/bmp.c csv-fast-reader/csv.c
TARGET = reconstruct-number

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Create build directory and compile
$(BUILD_DIR)/$(TARGET): $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $@

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean