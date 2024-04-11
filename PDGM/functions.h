#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "pdgm.h"

/* rand.c */
extern int32_t calculate_round_number(void);

/* init.c */
extern void init_game(GameState_t *);
extern void init_running_count(RunningCount_t *);

/* message.c */
extern void broadcast_message(char *);
extern char process_incoming_message(char *);

/* game.c */
extern int32_t run_game(GameState_t *, ParticipantProc_t *, ParticipantProc_t *);

/* process.c */
extern void destroy_participant_process(ParticipantProc_t *, int);
extern ParticipantProc_t *start_participant_process(char *);
extern void procprint(FILE *, char *);
extern void procread(ParticipantProc_t *, char *);

#endif
