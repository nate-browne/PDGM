#ifndef PDGM_H
#define PDGM_H

#define _POSIX_C_SOURCE 200809L

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
#include <errno.h>

#include "strings.h"

#define NAME "PDGM v1.0.0"

#define DEFAULT_GAME_NUMBER 50

// score constants
enum POINTS_OPTIONS {
  TWO_COOP = 3,
  ONE_COOP_GAIN = 5,
  ONE_COOP_LOSS = 0,
  NO_COOP = 1
};

// base number of rounds
#define BASE_ROUND_NUMBER 200
#define ROUND_PLUS_MINUS 11

// command line arguments
#define FIRST_PARTICIPANT 1
#define SECOND_PARTICIPANT 2

// Commands participants issue to interact
enum PARTICIPANT_COMMANDS {
  COOPERATE = 0,
  DEFECT = 1,
  NOOP = 2
};

typedef struct GameState {

  uint32_t p1_score;
  uint32_t p2_score;
  uint32_t total_rounds;
  int p1_previous_move;
  int p2_previous_move;
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
