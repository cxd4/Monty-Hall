#include <stdio.h>
#include "doors.h"

#include <stddef.h>
size_t wins  = 0;
size_t total = 0;

static void round_execute(unsigned int door_number, int switching);

int main(int argc, char* argv[])
{
    if (argc < 2)
        for (;;)
            round_execute(NUMBER_OF_DOORS, -1);
    return 0;
}

static void round_execute(unsigned int door_number, int switching)
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
        fputs("Which door is your final guess?  ", stdout);
        door_number = get_door_number();
    } else if (switching == 0) {
     /* Skip asking for final answer; just go to revealing the prize. */
    } else { /* Skip asking; automatically switch to a remaining door. */
        do {
            door_number = (door_number + 1) % NUMBER_OF_DOORS;
        } while (door_number == hint_number);
    }
    select_door(door_number);

    reveal_all_doors();
    if (current_guess() == winning_door()) {
        ++wins;
        puts("You win the car.");
    } else {
        puts("You picked a goat.  Too bad.");
    }
    ++total;
    printf(
        "Current win ratio:  %g percent (%lu rounds)\n\n",
        100 * (double)wins / (double)total,
        (unsigned long)total
    );
}
