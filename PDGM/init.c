#include "pdgm.h"
#include "functions.h"

void init_game(GameState_t *gs) {
  gs->p1_score = 0;
  gs->p2_score = 0;
  gs->total_rounds = calculate_round_number() + BASE_ROUND_NUMBER;
  gs->p1_previous_move = NOOP;
  gs->p2_previous_move = NOOP;
}

void init_running_count(RunningCount_t *rc) {
  rc->p1_wins = 0;
  rc->p2_wins = 0;
  rc->ties = 0;
}
