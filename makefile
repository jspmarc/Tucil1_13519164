CXX = g++
CPPFLAGS = -std=c++11 -O2 -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
BIN_DIR = bin/
SRC_DIR = src/
#INC_DIR = $(addprefix $(SRC_DIR),headers/)
#INC_FLAGS = -I$(INC_DIR)
TARGET = main

default: run

#$(addprefix $(BIN_DIR),helpers.o): $(addprefix $(SRC_DIR),helpers.cpp) $(addprefix $(INC_DIR),helpers.hpp)
	#$(CXX) $(CPPFLAGS) $(INC_FLAGS) -c $(addprefix $(SRC_DIR),helpers.cpp) -o $(addprefix $(BIN_DIR),helpers.o)

#$(TARGET): $(addprefix $(BIN_DIR),helpers.o) $(addprefix $(SRC_DIR),main.cpp)
	#$(CXX) $(CPPFLAGS) $(INC_FLAGS) $(addprefix $(BIN_DIR),helpers.o) $(addprefix $(SRC_DIR),main.cpp) -o $(addprefix $(BIN_DIR),$(TARGET))

$(TARGET): $(addprefix $(SRC_DIR),main.cpp)
	$(CXX) $(CPPFLAGS) $(addprefix $(SRC_DIR),main.cpp) -o $(addprefix $(BIN_DIR),$(TARGET))

run: $(TARGET)
	$(addprefix $(BIN_DIR),$(TARGET))

compile: $(TARGET)

clean:
	rm $(BIN_DIR)
