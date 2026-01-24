.PHONY: all release debug run run-debug test test-debug remake clean clean-all help

PROJ_NAME := ChessQDL
BUILD_DIR := build
BIN_PATH := $(BUILD_DIR)/bin/$(PROJ_NAME)

# Default target
all: debug

help:
	@echo "ChessQDL Makefile targets:"
	@echo ""
	@echo "Build targets:"
	@echo "  make release         - Build release binary (optimized)"
	@echo "  make debug           - Build debug binary with symbols (default)"
	@echo ""
	@echo "Run targets:"
	@echo "  make run             - Build and run release binary"
	@echo "  make run-debug       - Build and run debug binary"
	@echo ""
	@echo "Test targets:"
	@echo "  make test            - Build debug and run all tests"
	@echo "  make test-debug      - Alias for test"
	@echo ""
	@echo "Maintenance targets:"
	@echo "  make remake          - Clean and rebuild with debug"
	@echo "  make clean           - Remove build artifacts (bin, lib, CMake files)"
	@echo "                         Dependencies in build/_deps are preserved (fast rebuild)"
	@echo "  make clean-all       - Remove entire build directory (total cleanup)"
	@echo "  make help            - Show this help message"

# Release build
release: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Release .. && $(MAKE)

# Debug build
debug: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug .. && $(MAKE)

# Run the application (release)
run: release
	./$(BIN_PATH)

# Run the application (debug)
run-debug: debug
	./$(BIN_PATH)

# Run tests (debug build)
test: debug
	cd $(BUILD_DIR) && ctest --verbose

# Alias for test
test-debug: test

# Clean and rebuild
remake: clean all

# Clean build artifacts only (keeps dependencies in build/_deps for fast rebuild)
clean:
	@if [ -d "$(BUILD_DIR)" ]; then \
		echo "Cleaning build artifacts (keeping dependencies)..."; \
		rm -rf $(BUILD_DIR)/bin $(BUILD_DIR)/lib $(BUILD_DIR)/CMakeFiles \
		       $(BUILD_DIR)/Testing $(BUILD_DIR)/CMakeCache.txt \
		       $(BUILD_DIR)/cmake_install.cmake $(BUILD_DIR)/Makefile; \
		echo "Build cleaned. Dependencies preserved in $(BUILD_DIR)/_deps for fast rebuilds."; \
	fi

# Clean everything including dependencies (total nuke)
clean-all:
	@echo "Removing entire build directory..."
	rm -rf $(BUILD_DIR)
	@echo "Build directory completely removed."

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
