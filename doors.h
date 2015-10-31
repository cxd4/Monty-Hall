#ifndef _DOORS_H_
#define _DOORS_H_

#ifndef NUMBER_OF_DOORS
#define NUMBER_OF_DOORS         3
#endif

typedef struct {
    unsigned int has_prize         :  1;
    unsigned int currently_selected:  1;
    unsigned int revealed          :  1;
} door;

/*
 * game status updates
 */
extern void set_doors(void);
extern void select_door(unsigned int number);
extern void show_doors(void);
extern void reveal_all_doors(void);

/*
 * game status queries
 */
extern unsigned int get_door_number(void);
extern unsigned int current_guess(void);
extern unsigned int winning_door(void);
extern unsigned int hint_door(void);

#endif
