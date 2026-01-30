
# Makefile
BUILD_DIR := build

all:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	cmake --build $(BUILD_DIR) --verbose

run: all
	./$(BUILD_DIR)/vulkan_triangle

clean:
	rm -rf $(BUILD_DIR)
