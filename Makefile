CC = gcc
CFLAGS = -Wall -g
SRC = main.c game.c
OBJ = $(SRC:.c=.o)
EXEC = game

# Default target to build the game
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(EXEC)

# Run the game
run: $(EXEC)
	./$(EXEC)

# Target to save game
save: $(EXEC)
	./$(EXEC) save game_save.txt

# Target to load game
load: $(EXEC)
	./$(EXEC) load game_save.txt
