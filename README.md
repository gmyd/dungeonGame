# Dungeon Adventure Game

A simple text-based adventure game written in C, where you navigate through rooms, collect items, and fight creatures. The game includes features like saving and loading your progress, managing an inventory, and health tracking.

## Features

- **Explore Rooms**: Move between rooms in a dungeon using commands like `move up`, `move down`, `move left`, and `move right`.
- **Items**: Pick up items like a key, sword, or medicine that can help you in your journey.
- **Combat**: Fight creatures like goblins by using the `attack` command.
- **Save/Load Game**: Save your progress to a file and load it back later.
- **Inventory**: View the items you've collected using the `inventory` command.
- **Health Management**: Track and manage your health during the game, and use items like medicine to heal.
- **Room Descriptions**: Each room has a unique description and may contain items or creatures.

## Game Commands

- `move <direction>`: Move in the specified direction (`up`, `down`, `left`, `right`).
- `look`: View the current room's description and any items or creatures present.
- `pickup <item>`: Pick up an item from the room and add it to your inventory.
- `inventory`: Show the items in your inventory.
- `attack`: Attack the creature in the current room.
- `health`: Show current health.
- `save <filename>`: Save the current game state to a file.
- `load <filename>`: Load the game state from a saved file.
- `exit`: Exit the game.

## Building the Game

### Prerequisites

Make sure you have a C compiler (e.g., GCC) installed on your machine.

### Steps to Build

1. Clone or download the project to your local machine.
2. Navigate to the project directory.
3. Run the following command to compile the code:

```bash
gcc main.c game.c -o dungeonGame
```

```bash
./dungeonGame
```
