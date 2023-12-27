#ifndef PDGM_H
#define PDGM_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define NAME "PDGM v0.1.0"

#define WELCOME_STR "Welcome to %s!\n"
#define GAMES_PROMPT "Enter number of simulations to run (default is 3): "
#define RESULTS_STR "RESULTS:\np1 victories: %d\np2 victories: %d\nties: %d\nWinner: %s\n"

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

#endif
