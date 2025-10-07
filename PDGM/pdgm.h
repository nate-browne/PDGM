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

// smallest number of games we'll allow to be played
#define DEFAULT_GAME_NUMBER 50

// used in strtoul
#define PARSE_BASE 10

// score constants
enum POINTS_OPTIONS {
  TWO_COOP = 3,
  ONE_COOP_GAIN = 5,
  ONE_COOP_LOSS = 0,
  NO_COOP = 1
};

// base number of rounds
#define BASE_ROUND_NUMBER 200

// max range for round modifier.
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

// Winner results from the games
enum WINNER_RESULTS {
  P1_WINS = 0,
  P2_WINS = 1,
  TIE = 2
};

/**
 * This is the state remembered by any particular game.
 */
typedef struct GameState {

  uint32_t p1_score; // current score for participant 1
  uint32_t p2_score; // current score for participant 2
  uint32_t total_rounds; // how many rounds are in this game
  int32_t p1_previous_move; // what participant 1 did on the previous round
  int32_t p2_previous_move; // what participant 2 did on the previous round
} GameState_t;

/**
 * This is the state for each participant.
 */
typedef struct ParticipantProc {

  int fd_from; // stdout for the process
  int fd_to; // stdin for the process
  FILE *in; // file pointer for above file descriptor
  FILE *out; // file pointer for above file descriptor
  int pid; // process id
  char *name; // name of the participant
} ParticipantProc_t;

/**
 * This is the state for the entire set of games.
 */
typedef struct RunningCount {

  uint64_t *p1_scores; // final scores from each game for p1
  uint64_t *p2_scores; // final scores from each game for p2
} RunningCount_t;

#endif
