# Compiler
CXX = g++

# Compiler flags
# -Iinclude permet de trouver les fichiers .h dans le dossier include
CXXFLAGS = -Wall -g -Iinclude

# Target executable
TARGET = analog

# Dossiers
SRC_DIR = src
OBJ_DIR = obj

# Source files (on cherche les fichiers dans src/)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files (on place les .o dans le dossier obj/)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default rule
all: $(TARGET)

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
# On crée le dossier obj s'il n'existe pas
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run: $(TARGET)
	./$(TARGET)

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET)