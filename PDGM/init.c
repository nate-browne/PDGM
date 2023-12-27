#include "pdgm.h"
#include "functions.h"

void init_game(GameState_t *gs) {
  gs->p1_score = 0;
  gs->p2_score = 0;
  gs->total_rounds = calculate_round_number() + BASE_ROUND_NUMBER;
  gs->p1_previous_move = NULL;
  gs->p2_previous_move = NULL;
}
