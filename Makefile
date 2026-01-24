.PHONY: all release debug compile_commands run test remake clean help

PROJ_NAME := ChessQDL
BUILD_DIR := build
BIN_PATH := $(BUILD_DIR)/bin/$(PROJ_NAME)

# Default target
all: build

help:
	@echo "ChessQDL Makefile targets:"
	@echo "  make release         - Build release binary"
	@echo "  make debug           - Build debug binary with symbols (default)"
	@echo "  make run             - Build and run release binary"
	@echo "  make test            - Run tests"
	@echo "  make remake          - Clean and rebuild"
	@echo "  make clean           - Remove build directory"
	@echo "  make help            - Show this help message"

# Release build
release: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Release .. && $(MAKE)

# Debug build
debug: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug .. && $(MAKE)

# Run the application
run: release
	./$(BIN_PATH)

# Run tests
test: $(BUILD_DIR)
	cd $(BUILD_DIR) && ctest --verbose

# Clean and rebuild
remake: clean all

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
