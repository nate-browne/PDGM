#ifndef PDGM_H
#define PDGM_H

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

#include "strings.h"

#define NAME "PDGM v0.1.0"

#define DEFAULT_GAME_NUMBER 3

// score constants
#define TWO_COOP 3
#define ONE_COOP_GAIN 5
#define ONE_COOP_LOSS 0
#define NO_COOP 1

// base number of rounds
#define BASE_ROUND_NUMBER 200
#define ROUND_PLUS_MINUS 11

typedef struct GameState {

  uint32_t p1_score;
  uint32_t p2_score;
  uint32_t total_rounds;
  char* p1_previous_move;
  char* p2_previous_move;
} GameState_t;

typedef struct ParticipantProc {

  int fd_from; // stdout for the process
  int fd_to; // stdin for the process
  FILE *in; // file pointer for above file descriptor
  FILE *out; // file pointer for above file descriptor
  int pid; // process id
  char *name; // name of the participant
} ParticipantProc_t;

typedef struct RunningCount {

  int32_t p1_wins;
  int32_t p2_wins;
  int32_t ties;
} RunningCount_t;

#endif
