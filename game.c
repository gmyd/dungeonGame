#include "game.h"
#include <stdio.h>
#include <stdlib.h>

Player player;

void init_game()
{
    player.health = 100;
    player.strength = 10;
    player.inventory_count = 0;

    // Initialize Rooms
    Room *room1 = create_room("You are in a dark dungeon room. There's a faint light to the north.");
    Room *room2 = create_room("This room is brighter, with moss on the walls. There's a table here.");
    Room *room3 = create_room("A cold, damp room with the sound of water dripping.");
    Room *room4 = create_room("A small room with an eerie atmosphere, a faint sound of whispers.");
    Room *room5 = create_room("A vast room with a large window overlooking the forest.");

    // Connecting rooms
    room1->up = room2;
    room2->down = room1;
    room2->up = room3;
    room3->down = room2;
    room3->up = room4;
    room4->down = room3;
    room4->right = room5;
    room5->left = room4;

    // Add Items
    room1->items[room1->item_count++] = create_item("Key", "A rusty old key.", 0);
    room2->items[room2->item_count++] = create_item("Sword", "A sharp, shiny sword.", 0);
    room3->items[room3->item_count++] = create_item("Medicine", "A healing potion.", 20); // Medicine item
    room4->items[room4->item_count++] = create_item("Shield", "A sturdy shield.", 0);
    room5->items[room5->item_count++] = create_item("Scroll", "A magical scroll.", 0);

    // Add Creature
    room3->creature = (Creature *)malloc(sizeof(Creature));
    room3->creature->name = strdup("Goblin");
    room3->creature->health = 30;
    room3->creature->strength = 5;

    player.current_room = room1;
}

void cleanup_game()
{
    free_room(player.current_room);
    for (int i = 0; i < player.inventory_count; i++)
    {
        free_item(player.inventory[i]);
    }
}

Room *create_room(const char *desc)
{
    Room *room = (Room *)malloc(sizeof(Room));
    room->description = strdup(desc);
    room->item_count = 0;
    room->creature = NULL;
    room->up = room->down = room->left = room->right = NULL;
    return room;
}

void free_room(Room *room)
{
    if (room)
    {
        free(room->description);
        for (int i = 0; i < room->item_count; i++)
        {
            free_item(room->items[i]);
        }
        if (room->creature)
        {
            free(room->creature->name);
            free(room->creature);
        }
        free(room);
    }
}

Item *create_item(const char *name, const char *desc, int health_bonus)
{
    Item *item = (Item *)malloc(sizeof(Item));
    item->name = strdup(name);
    item->description = strdup(desc);
    item->health_bonus = health_bonus; // Set the health bonus for medicine
    return item;
}

void free_item(Item *item)
{
    if (item)
    {
        free(item->name);
        free(item->description);
        free(item);
    }
}

void handle_command(const char *command)
{
    char cmd[50], arg[50];
    sscanf(command, "%s %49[^\n]", cmd, arg);

    if (strcmp(cmd, "move") == 0)
    {
        move_player(arg);
    }
    else if (strcmp(cmd, "look") == 0)
    {
        look_room();
    }
    else if (strcmp(cmd, "pickup") == 0)
    {
        pickup_item(arg);
    }
    else if (strcmp(cmd, "inventory") == 0)
    {
        show_inventory();
    }
    else if (strcmp(cmd, "attack") == 0)
    {
        attack_creature();
    }
    else if (strcmp(cmd, "save") == 0)
    {
        save_game(arg);
    }
    else if (strcmp(cmd, "load") == 0)
    {
        load_game(arg);
    }
    else if (strcmp(cmd, "list") == 0)
    {
        list_saved_games();
    }
    else if (strcmp(cmd, "exit") == 0)
    {
        cleanup_game();
        exit(0);
    }
    else if (strcmp(cmd, "health") == 0)
    { // Command to check health
        check_health();
    }
    else
    {
        printf("Invalid command!\n");
    }
}

void move_player(const char *direction)
{
    Room *next_room = NULL;

    if (strcmp(direction, "up") == 0)
        next_room = player.current_room->up;
    else if (strcmp(direction, "down") == 0)
        next_room = player.current_room->down;
    else if (strcmp(direction, "left") == 0)
        next_room = player.current_room->left;
    else if (strcmp(direction, "right") == 0)
        next_room = player.current_room->right;

    if (next_room)
    {
        player.current_room = next_room;
        printf("You moved %s.\n", direction);
        look_room();
    }
    else
    {
        printf("You can't move in that direction.\n");
    }
}

void look_room()
{
    printf("%s\n", player.current_room->description);
    if (player.current_room->item_count > 0)
    {
        printf("Items in this room:\n");
        for (int i = 0; i < player.current_room->item_count; i++)
        {
            printf("- %s\n", player.current_room->items[i]->name);
        }
    }
    if (player.current_room->creature)
    {
        printf("A %s is here!\n", player.current_room->creature->name);
    }
}

void pickup_item(const char *item_name)
{
    // Search for the item in the room and add it to the player's inventory.
    for (int i = 0; i < player.current_room->item_count; i++)
    {
        if (strcmp(player.current_room->items[i]->name, item_name) == 0)
        {
            if (player.inventory_count < MAX_INVENTORY)
            {
                player.inventory[player.inventory_count++] = player.current_room->items[i];
                printf("You picked up %s.\n", item_name);
                return;
            }
            else
            {
                printf("Your inventory is full!\n");
                return;
            }
        }
    }
    printf("No such item here.\n");
}

void attack_creature()
{
    if (player.current_room->creature)
    {
        Creature *creature = player.current_room->creature;
        printf("You attack the %s!\n", creature->name);
        player.health -= creature->strength; // Decrease player's health after attack
        printf("You take %d damage. Your health is now %d.\n", creature->strength, player.health);
        creature->health -= player.strength;
        if (creature->health <= 0)
        {
            printf("You defeated the %s!\n", creature->name);
            free(creature->name);
            free(creature);
            player.current_room->creature = NULL;
        }
    }
    else
    {
        printf("There is no creature to attack here.\n");
    }
}

void check_health()
{
    printf("Your health is %d.\n", player.health);
}

// New functions to handle inventory, save/load, and listing saved games

void show_inventory()
{
    if (player.inventory_count == 0)
    {
        printf("Your inventory is empty.\n");
        return;
    }

    printf("Your inventory contains:\n");
    for (int i = 0; i < player.inventory_count; i++)
    {
        printf("- %s: %s\n", player.inventory[i]->name, player.inventory[i]->description);
    }
}

void save_game(const char *filepath)
{
    FILE *file = fopen(filepath, "w");
    if (file == NULL)
    {
        printf("Failed to save the game.\n");
        return;
    }

    fprintf(file, "%d\n", player.health);
    fprintf(file, "%d\n", player.strength);
    // Save other player data and room state if needed

    fclose(file);
    printf("Game saved successfully.\n");
}

void load_game(const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        printf("Failed to load the game.\n");
        return;
    }

    fscanf(file, "%d", &player.health);
    fscanf(file, "%d", &player.strength);
    // Load other player data and room state if needed

    fclose(file);
    printf("Game loaded successfully.\n");
}

void list_saved_games()
{
    printf("Listing saved games...\n");
    // List available saved games from the directory or file system
}
