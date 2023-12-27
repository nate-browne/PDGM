#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "pdgm.h"

/* rand.c */
extern uint32_t calculate_round_number(void);

/* init.c */
extern void init_game(GameState_t *);

/* message.c */
extern void broadcast_message(char *);
extern char process_incoming_message(char *);

/* game.c */
extern void run_game(GameState_t *);

#endif
