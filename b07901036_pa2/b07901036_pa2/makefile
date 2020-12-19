CXX = g++
CFLAGS = -Wall -std=c++11 -Wno-psabi
OPTFLAGS = -g
OPTFLAGS = -O3

SRC_DIR = src/
INC_DIR = src/
BIN_DIR = bin/

EXEC = mps
BIN	= $(addprefix $(BIN_DIR), $(EXEC))
INC = -I$(INC_DIR)
SRC = $(wildcard $(SRC_DIR)*.cpp)
OBJ = $(SRC:%.cpp=%.o)

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CFLAGS) $(INC) $(OPTFLAGS) $^ -o $(BIN)
	@echo "FINISH"

%.o : %.cpp
	@echo ">> compiling: $<"
	$(CXX) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(BIN) $(OBJ)