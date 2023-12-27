#ifndef PDGM_H
#define PDGM_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

//#define DEBUG

// kind of messy, but this whole mess allows us to throw in
// assert debug statements without mass commenting them out later
// just comment out line 50
// to be clear, I took this from a book and didn't come up with this macro
// myself
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - \033[91mFAILED!!\033[0m", #n); \
printf(" on %s ", __DATE__); \
printf("at %s ", __TIME__); \
printf("in file %s ", __FILE__); \
printf("on line %d\n", __LINE__); \
exit(1);}
#endif

#define NAME "PDGM v0.1.0"

#define GAMES_PROMPT "Enter number of games to run (default is 3): "

#define DEFAULT_GAME_NUMBER 3

// score constants
#define TWO_COOP 3
#define ONE_COOP_GAIN 5
#define ONE_COOP_LOSS 0
#define NO_COOP 1

// base number of rounds
#define BASE_ROUND_NUMBER 200

typedef struct GameState {

  uint32_t p1_score;
  uint32_t p2_score;
  uint32_t total_rounds;
  uint32_t current_round;
} GameState_t;

#endif
