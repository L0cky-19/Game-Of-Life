CXX = g++
CXXFLAGS = -I"C:\SFML\include" -I.
LDFLAGS = -L"C:\SFML\lib"
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Pour les tests
TEST_CXXFLAGS = -I. -I"C:/msys64/mingw64/include/gtest" -I"C:/msys64/mingw64/include" -static
TEST_LDFLAGS = -L"C:/msys64/mingw64/lib"
TEST_LIBS = -static -static-libgcc -static-libstdc++ -lgtest -lgtest_main -lpthread

# Dossiers
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests

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
       $(SRC_DIR)/file-handler/FileHandler.cpp \
       $(SRC_DIR)/input/Config.cpp \
	   $(SRC_DIR)/renderer/Subject.cpp


# Fichiers pour les tests
TEST_SRCS = $(TEST_DIR)/GridTest.cpp
TEST_DEPS = $(SRC_DIR)/Grid.cpp \
           $(SRC_DIR)/Cell.cpp \
           $(SRC_DIR)/evolution-strategy/ClassicEvolution.cpp

# Génération des chemins des fichiers objets
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/tests/%.o)
TEST_DEPS_OBJS = $(TEST_DEPS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/test_deps/%.o)

# Exécutables
TARGET = $(BUILD_DIR)/game-of-life
TEST_TARGET = $(BUILD_DIR)/test-runner

# Règle par défaut
all: create_dirs $(TARGET)
	copy C:\SFML\bin\*.dll $(BUILD_DIR)
	$(TARGET)

# Règle pour les tests
test: create_dirs $(TEST_TARGET)
	@echo Running tests...
	@cd $(BUILD_DIR) && set GTEST_COLOR=1 && test-runner.exe --gtest_break_on_failure || exit 0
	@echo Test execution completed.

# Création des répertoires nécessaires
create_dirs:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@if not exist "$(BUILD_DIR)\renderer" mkdir "$(BUILD_DIR)\renderer"
	@if not exist "$(BUILD_DIR)\game-state" mkdir "$(BUILD_DIR)\game-state"
	@if not exist "$(BUILD_DIR)\evolution-strategy" mkdir "$(BUILD_DIR)\evolution-strategy"
	@if not exist "$(BUILD_DIR)\file-handler" mkdir "$(BUILD_DIR)\file-handler"
	@if not exist "$(BUILD_DIR)\input" mkdir "$(BUILD_DIR)\input"
	@if not exist "$(BUILD_DIR)\tests" mkdir "$(BUILD_DIR)\tests"
	@if not exist "$(BUILD_DIR)\test_deps" mkdir "$(BUILD_DIR)\test_deps"
	@if not exist "$(BUILD_DIR)\test_deps\evolution-strategy" mkdir "$(BUILD_DIR)\test_deps\evolution-strategy"

# Création de l'exécutable principal
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

# Création de l'exécutable de test
$(TEST_TARGET): $(TEST_OBJS) $(TEST_DEPS_OBJS)
	$(CXX) -o $(TEST_TARGET) $^ $(TEST_LDFLAGS) $(TEST_LIBS)

# Compilation des fichiers source principaux
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(@D)" mkdir "$(@D)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation des fichiers de test
$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@if not exist "$(@D)" mkdir "$(@D)"
	$(CXX) $(TEST_CXXFLAGS) -c $< -o $@

# Compilation des dépendances de test
$(BUILD_DIR)/test_deps/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(@D)" mkdir "$(@D)"
	$(CXX) $(TEST_CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

.PHONY: all clean create_dirs test
