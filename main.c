#include <stdio.h>
#include "doors.h"

#include <stddef.h>
size_t wins  = 0;
size_t total = 0;

static void round_execute(void);

int main(void)
{
    for (;;)
        round_execute();
    return 0;
}

static void round_execute(void)
{
 /* Randomly arrange what's behind all three doors. */
    set_doors();

    puts("Choose a door:");
    show_doors();
    printf("Pick from 1 to %d (0 for random):  ", NUMBER_OF_DOORS);
    select_door(get_door_number());

    printf(
        "Before I reveal what's behind door %u, here's door %u.\n",
        current_guess() + 1, hint_door() + 1
    );
    fputs("Which door is your final guess?  ", stdout);
    select_door(get_door_number());

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
