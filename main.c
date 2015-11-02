#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "doors.h"

#include <stddef.h>
size_t wins, total;

static void round_execute(unsigned long door_number, long switching);

int main(int argc, char* argv[])
{
    unsigned long door_number;
    long switching;
    register size_t limit;

    limit = 1;
    door_number = NUMBER_OF_DOORS; /* Invalidate constant door requests. */
    switching = -1; /* Ask every time whether to switch--no automaticion. */
    srand((unsigned int)time(NULL));

    if (argc >= 2)
        limit = strtoul(argv[1], NULL, 0);
    if (argc >= 3)
        switching = strtol(argv[2], NULL, 0);
    if (argc >= 4)
        door_number = strtoul(argv[3], NULL, 0);

    while (total++ < limit)
        round_execute(door_number, switching);
    return 0;
}

static const char* win_or_lose[] = {
    "You picked a goat.  Too bad.",
    "You win the car!",
};
static void round_execute(unsigned long door_number, long switching)
{
    unsigned int hint_number;

 /* Randomly arrange what's behind all three doors. */
    set_doors();

    while (door_number >= NUMBER_OF_DOORS) {
        puts("Choose a door:");
        show_doors();
        printf("Pick from 1 to %d:  ", NUMBER_OF_DOORS);
        door_number = get_door_number();
    }
    select_door(door_number);

    hint_number = hint_door();
    printf(
        "Before I reveal what's behind door %u, here's door %u.\n",
        door_number + 1, hint_number + 1
    );
    if (switching < 0) { /* Ask whether to switch. */
        do {
            printf("Which door is your final guess?  ");
            door_number = get_door_number();
        } while (door_number >= NUMBER_OF_DOORS);
    } else if (switching == 0) {
     /* Skip asking for final answer; just go to revealing the prize. */
    } else { /* Skip asking; automatically switch to a remaining door. */
        do {
            door_number = (door_number + 1) % NUMBER_OF_DOORS;
        } while (door_number == hint_number);
    }
    select_door(door_number);

    reveal_all_doors();
    hint_number = (winning_door() == door_number) ? 1 : 0;
    puts(win_or_lose[hint_number]);
    wins += hint_number;

    printf(
        "Current win ratio:  %g percent (%lu rounds)\n\n",
        100. * wins / total,
        (unsigned long)total
    );
}
