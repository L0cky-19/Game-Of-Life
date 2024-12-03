CXX = g++
CXXFLAGS = -I/mnt/c/SFML/include -I.
LDFLAGS = -L/mnt/c/SFML/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

# Source files
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/renderer/GraphicRenderer.cpp \
       $(SRC_DIR)/renderer/ConsoleRenderer.cpp

# Generate object file paths in the build directory
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executable name
TARGET = $(BUILD_DIR)/game-of-life

# Default rule
all: create_dirs $(TARGET)
	cp /mnt/c/SFML/bin/*.dll $(BUILD_DIR)/
	./$(TARGET)

# Create necessary directories
create_dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/renderer

# Link executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean create_dirs
