CXX = g++
CXXFLAGS = -std=c++14 -I/opt/homebrew/include -I.
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

# Fichiers source
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/Game.cpp \
       $(SRC_DIR)/Grid.cpp \
       $(SRC_DIR)/Cell.cpp \
       $(SRC_DIR)/renderer/ConsoleRenderer.cpp \
       $(SRC_DIR)/renderer/GraphicRenderer.cpp \
       $(SRC_DIR)/evolution-strategy/ClassicEvolution.cpp \
       $(SRC_DIR)/evolution-strategy/HighLifeEvolution.cpp \
       $(SRC_DIR)/game-state/PlayState.cpp \
       $(SRC_DIR)/game-state/PauseState.cpp \
	   $(SRC_DIR)/file-handler/FileHandler.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TARGET = $(BUILD_DIR)/game-of-life

all: create_dirs $(TARGET)
	cp /opt/homebrew/lib/*.dylib $(BUILD_DIR)
	$(TARGET)

create_dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/renderer
	mkdir -p $(BUILD_DIR)/game-state
	mkdir -p $(BUILD_DIR)/evolution-strategy
	mkdir -p $(BUILD_DIR)/file-handler

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean create_dirs