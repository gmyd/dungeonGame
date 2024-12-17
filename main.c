#include "game.h"

int main()
{
    char input[100];
    printf("Welcome to the Dungeon Adventure Game!\n");
    init_game();

    while (1)
    {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        handle_command(input);
    }

    return 0;
}
