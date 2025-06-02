CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I. -I./utils -I./rooms
LDFLAGS = -lrt # librt 라이브러리 연결

# Source files
SRC_MAIN = main.c
SRC_STATE = game_state.c
SRC_COMMAND = command_parser.c
SRC_ROOMS = rooms/room1.c rooms/room2.c rooms/room3.c
SRC_UTILS = utils/utils.c

# Object files
OBJ_MAIN = $(SRC_MAIN:.c=.o)
OBJ_STATE = $(SRC_STATE:.c=.o)
OBJ_COMMAND = $(SRC_COMMAND:.c=.o)
OBJ_ROOMS = $(SRC_ROOMS:.c=.o)
OBJ_UTILS = $(SRC_UTILS:.c=.o)

# Directories
ROOM_DIR = rooms
UTILS_DIR = utils

# Headers
VPATH = . $(ROOM_DIR) $(UTILS_DIR)

# Executable name
TARGET = trojan_escape

all: $(TARGET)

$(TARGET): $(OBJ_MAIN) $(OBJ_STATE) $(OBJ_COMMAND) $(OBJ_ROOMS) $(OBJ_UTILS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# Rule for .c to .o compilation
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Specific rules for files in subdirectories
$(ROOM_DIR)/%.o: $(ROOM_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(UTILS_DIR)/%.o: $(UTILS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(ROOM_DIR)/*.o $(UTILS_DIR)/*.o $(TARGET)
