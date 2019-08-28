CC=gcc

SRC_DIR=./

SRC_EXT=cpp

INCLUDE_DIR=./

OBJ_DIR=obj

# Directory of the executable
BIN_DIR=./

# Compile flags
CFLAGS= -lstdc++ \
				-std=c++11 \

# Warning flags
WFLAGS= -Wall \
				-Wextra

# Set the name of the project here
EXE=run

SOURCES := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJECTS := $(SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)

all: $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(EXE)

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(WFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm $(OBJECTS) $(EXE) -v

run:
	./$(BIN_DIR)/$(EXE)
