#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INVENTORY 5
#define MAX_DESC_LEN 256
#define MAX_ITEMS 10

// Struct Definitions
typedef struct Item
{
    char *name;
    char *description;
    int health_bonus; // Health bonus for medicine item
} Item;

typedef struct Creature
{
    char *name;
    int health;
    int strength;
} Creature;

typedef struct Room
{
    char *description;
    Item *items[MAX_ITEMS];
    int item_count;
    Creature *creature;
    struct Room *up, *down, *left, *right;
} Room;

typedef struct Player
{
    int health;
    int strength;
    int inventory_count;
    Item *inventory[MAX_INVENTORY];
    Room *current_room;
} Player;

// Global Variables
extern Player player;

// Function Prototypes
void init_game();
void cleanup_game();
void handle_command(const char *command);
void move_player(const char *direction);
void look_room();
void pickup_item(const char *item_name);
void show_inventory();
void attack_creature();
void save_game(const char *filepath);
void load_game(const char *filepath);
void list_saved_games();
Room *create_room(const char *desc);
void free_room(Room *room);
Item *create_item(const char *name, const char *desc, int health_bonus);
void free_item(Item *item);
void check_health(); // New function to check player's health

#endif // GAME_H
