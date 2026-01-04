# Makefile
BUILD_DIR := build

all:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

run: all
	./$(BUILD_DIR)/vulkan_example

clean:
	rm -rf $(BUILD_DIR)

