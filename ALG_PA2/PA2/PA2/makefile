# Directories
SRC_DIR = src
BIN_DIR = bin
EXEC = mps

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -O2

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Target
$(BIN_DIR)/$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(SRC_DIR)/*.o $(BIN_DIR)/$(EXEC)
