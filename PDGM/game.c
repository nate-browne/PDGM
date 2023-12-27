#include "pdgm.h"
#include "functions.h"

static int32_t process_round_result(GameState_t *gs, char p1_decision, char p2_decision) {

}

int32_t run_game(GameState_t *gs) {

  for(int i = 0; i < gs->total_rounds; ++i) {

  }

  if(gs->p1_score > gs->p2_score) {
    return 0;
  } else if(gs->p1_score < gs->p2_score) {
    return 1;
  } else {
    return 2;
  }
}
