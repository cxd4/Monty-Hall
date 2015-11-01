#include <stdio.h>
#include <stdlib.h>

#include <limits.h>
#include <errno.h>
#include <time.h>
#include "input.h"

char* get_string(void)
{
    static char text_buffer[256];
    int character;
    register size_t i;

    do {
        for (i = 0; i < sizeof(text_buffer); i++) {
            text_buffer[i] = '\0';
            character = getchar();

            if (character == '\n')
                return &(text_buffer[0]);
            if (character < 32 || character > 126)
                return NULL;
            text_buffer[i] = (char)character;
        }
    } while (text_buffer[0] == '\0');
    return NULL;
}

signed char get_Boolean(void)
{
    char * text;
    signed long input;

    text = get_string();
    if (text == NULL)
        return -1;

    input = strtol(text, NULL, 0);
    if (errno == ERANGE) {
        errno = 0;
        return -1;
    }

    if (input != 0)
        return 1;
    return (text[0] & 1); /* starts with 'Y'(es), 'N'(o), etc. */
}

unsigned int get_whole_number(void)
{
    char * text;
    unsigned long input;

    text = get_string();
    if (text == NULL)
        return get_random_whole_number();

    input = strtoul(text, NULL, 0);
    if (input > UINT_MAX)
        return get_random_whole_number();

    return ((unsigned int)(input));
}

unsigned int get_random_whole_number(void)
{
    static unsigned int seed;
    unsigned int random_number;

    if (seed == 0) { /* Only set once, or time might work against us. */
        seed = (unsigned int)time(NULL);
        srand(seed);
    }
    random_number = (unsigned int)rand();
    return (random_number);
}
