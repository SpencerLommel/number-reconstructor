CC = gcc
CFLAGS = -Wall -Wextra
BUILD_DIR = build

# Source files
COMMON_SRCS = bmp/bmp.c csv-fast-reader/csv.c

# Targets
TARGETS = demo line-number


# Default target
all: $(TARGETS:%=$(BUILD_DIR)/%)

# Rules for each target
$(BUILD_DIR)/demo: demo.c $(COMMON_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) demo.c $(COMMON_SRCS) -o $@

$(BUILD_DIR)/line-number: line-number.c $(COMMON_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) line-number.c $(COMMON_SRCS) -o $@

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean