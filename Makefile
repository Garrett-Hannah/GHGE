#Define vars

CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17 -I/usr/include/glm
LDFLAGS = -lGL -lGLU -lSDL2 -lGLEW



ROOT_DIR = .

SRC_DIRS = src Tools Engine


SRC = $(wildcard $(ROOT_DIR)/main.cpp) $(shell find $(SRC_DIRS) -name '*.cpp')
TEST_SRC = $(wildcard $(ROOT_DIR)/test.cpp) $(shell find $(SRC_DIRS) -name '*.cpp')

OBJ = $(SRC:.cpp=.o)
TEST_OBJ= $(TEST_SRC:.cpp=.o)

TARGET = my_program
TEST_TARGET = tests 

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)





%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)


.PHONY: test 
test: $(TEST_TARGET)
	./$(TEST_TARGET)
