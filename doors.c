#include <stdio.h>
#include "doors.h"
#include "input.h"

static door doors[NUMBER_OF_DOORS];

void set_doors(void)
{
    register unsigned int i;
    const unsigned int random_door = get_random_whole_number();

    for (i = 0; i < NUMBER_OF_DOORS; i++) {
        doors[i].has_prize
      = doors[i].currently_selected
      = doors[i].revealed
      = 0;
    }
    doors[random_door % NUMBER_OF_DOORS].has_prize = 1;
    return;
}

void select_door(unsigned int number)
{
    register int i;

    for (i = 0; i < NUMBER_OF_DOORS; i++)
        doors[i].currently_selected = 0;
    doors[number % NUMBER_OF_DOORS].currently_selected = 1;
    return;
}

static const char outcomes[][6] = {
    "\tGOAT", "\tCAR",
};
void show_doors(void)
{
    register unsigned int i;

    for (i = 0; i < NUMBER_OF_DOORS; i++)
        if (doors[i].revealed)
            printf(outcomes[doors[i].has_prize]);
        else
            printf("\t#%u", i + 1);
    putchar('\n');
    return;
}

void reveal_all_doors(void)
{
    register int i;

    for (i = 0; i < NUMBER_OF_DOORS; i++)
        doors[i].revealed = 1;
    show_doors();
    return;
}

unsigned int get_door_number(void)
{
/*
 * User enters a one-based door number (from 1 to N max doors).
 * Registerd door ID becomes zero-based.
 */
    return (get_whole_number() - 1);
}

unsigned int winning_door(void)
{
    register unsigned int i;

    for (i = 0; i < NUMBER_OF_DOORS; i++)
        if (doors[i].has_prize)
            return (i);
    return (i);
}

unsigned int hint_door(void)
{
    static unsigned int losing_doors[NUMBER_OF_DOORS - 1];
    unsigned int random_hint;
    register unsigned int i, j;

    j = 0;
    for (i = 0; i < NUMBER_OF_DOORS; i++) {
        if (doors[i].has_prize || doors[i].currently_selected)
            continue;
        losing_doors[j++] = i;
    }

    random_hint = losing_doors[get_random_whole_number() % j];
    doors[random_hint].revealed = 1;
    show_doors();
    doors[random_hint].revealed = 0;
    return (random_hint);
}
