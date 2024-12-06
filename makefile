CXX = g++
CXXFLAGS = -I"C:\SFML\include" -I.
LDFLAGS = -L"C:\SFML\lib"
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Dossiers
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
	   $(SRC_DIR)/renderer/Subject.cpp \
       $(SRC_DIR)/evolution-strategy/ClassicEvolution.cpp \
       $(SRC_DIR)/evolution-strategy/HighLifeEvolution.cpp \
       $(SRC_DIR)/game-state/PlayState.cpp \
       $(SRC_DIR)/game-state/PauseState.cpp \
	   $(SRC_DIR)/file-handler/FileHandler.cpp \

# Génération des chemins des fichiers objets dans build/
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Nom de l'exécutable
TARGET = $(BUILD_DIR)/game-of-life

# Règle par défaut
all: create_dirs $(TARGET)
	copy C:\SFML\bin\*.dll $(BUILD_DIR)
	$(TARGET)

# Création des répertoires nécessaires
BUILD_DIRS = $(BUILD_DIR) \
             $(BUILD_DIR)/renderer \
             $(BUILD_DIR)/game-state \
             $(BUILD_DIR)/evolution-strategy

create_dirs:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@if not exist "$(BUILD_DIR)\renderer" mkdir "$(BUILD_DIR)\renderer"
	@if not exist "$(BUILD_DIR)\game-state" mkdir "$(BUILD_DIR)\game-state"
	@if not exist "$(BUILD_DIR)\evolution-strategy" mkdir "$(BUILD_DIR)\evolution-strategy"
	@if not exist "$(BUILD_DIR)\file-handler" mkdir "$(BUILD_DIR)\file-handler"

# Création de l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

# Règle de compilation pour les fichiers source
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(@D) mkdir $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

.PHONY: all clean create_dirs
