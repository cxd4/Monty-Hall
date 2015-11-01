#include <stdio.h>
#include <stdlib.h>
#include "doors.h"

#include <errno.h>
#include <limits.h>

#include <stddef.h>
size_t wins  = 0;
size_t total = 0, limit = 1;

static void round_execute(unsigned int door_number, int switching);

int main(int argc, char* argv[])
{
    unsigned long door_number;
    long switching;

    door_number = NUMBER_OF_DOORS; /* Invalidate constant door requests. */
    switching = -1; /* Ask every time whether to switch--no automaticion. */

    if (argc >= 2)
        limit = strtoul(argv[1], NULL, 0);

    if (argc >= 3)
        switching = strtol(argv[2], NULL, 0);

    if (argc >= 4)
        door_number = strtoul(argv[3], NULL, 0);
    if (errno == ERANGE || door_number > UINT_MAX)
        door_number = NUMBER_OF_DOORS;

    while (total++ < limit)
        round_execute(door_number, switching);
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
    printf(
        "Current win ratio:  %g percent (%lu rounds)\n\n",
        100 * (double)wins / (double)total,
        (unsigned long)total
    );
}
