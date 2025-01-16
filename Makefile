# Example Makefile with main.cpp in the root directory

# Define variables
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17 -I/usr/include/glm
LDFLAGS = -lGL -lGLU -lSDL2 -lGLEW

# Root and subdirectories
ROOT_DIR = .
SRC_DIRS = src Tools Engine 

# Include main.cpp from root directory and search for .cpp files in subdirectories
SRC = $(wildcard $(ROOT_DIR)/main.cpp) $(shell find $(SRC_DIRS) -name '*.cpp')
OBJ = $(SRC:.cpp=.o)

TARGET = my_program

# Rule to build the target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile .cpp files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove compiled files
.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)

