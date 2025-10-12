#include "pdgm.h"
#include "functions.h"

/**
 * Basic function that takes in a pointer to a GameState_t and
 * sets it up. Set the scores to 0, get the total number of rounds
 * we will play (200 +/- [0,11)), then set the previous moves to NOOP
 */
void init_game(GameState_t *gs) {
  gs->p1_score = 0;
  gs->p2_score = 0;
  gs->total_rounds = calculate_round_number() + BASE_ROUND_NUMBER;
  gs->p1_previous_move = NOOP;
  gs->p2_previous_move = NOOP;
}

/**
 * Basic function that takes in a pointer to a RunningCount_t and
 * sets it up. Initializes both score arrays with the number of games
 * we'll be playing
 */
void init_running_count(RunningCount_t *rc, const uint64_t num_games) {
  rc->p1_scores = calloc(num_games, sizeof(uint64_t));
  rc->p2_scores = calloc(num_games, sizeof(uint64_t));
}
