#include "pdgm.h"
#include "functions.h"

static int32_t process_round_result(GameState_t *gs, int p1_decision, int p2_decision) {

  gs->p1_previous_move = p1_decision;
  gs->p2_previous_move = p2_decision;

  if(p1_decision == COOPERATE && p2_decision == COOPERATE) {
    gs->p1_score += TWO_COOP;
    gs->p2_score += TWO_COOP;
  } else if(p1_decision == COOPERATE && p2_decision == DEFECT) {
    gs->p2_score += ONE_COOP_GAIN;
  } else if(p1_decision == DEFECT && p2_decision == COOPERATE) {
    gs->p1_score += ONE_COOP_GAIN;
  } else {
    gs->p1_score += NO_COOP;
    gs->p2_score += NO_COOP;
  }
}

int32_t run_game(GameState_t *gs, ParticipantProc_t *p1, ParticipantProc_t *p2) {

  char buffer[BUFSIZ] = {0};
  int p1_move, p2_move;

  for(uint32_t i = 0; i < gs->total_rounds; ++i) {
    // first, print the round number
    snprintf(buffer, BUFSIZ, ROUND_STR, i + 1);
    procprint(p1, buffer);
    procprint(p2, buffer);
    memset(buffer, '\0', BUFSIZ);
  
    // next, print the opponent's previous move
    sprintf(buffer, BUFSIZ, OPP_PREVIOUS_MOVE_STR, gs->p2_previous_move);
    procprint(p1, buffer);
    memset(buffer, '\0', BUFSIZ);
  
    sprintf(buffer, BUFSIZ, OPP_PREVIOUS_MOVE_STR, gs->p1_previous_move);
    procprint(p2, buffer);
    memset(buffer, '\0', BUFSIZ);
  
    // pull move from each player
    procread(p1, buffer);
    p1_move = atoi(buffer);
    memset(buffer, '\0', BUFSIZ);
  
    procread(p2, buffer);
    p2_move = atoi(buffer);
    memset(buffer, '\0', BUFSIZ);

    process_round_result(gs, p1_move, p2_move);
  }

  if(gs->p1_score > gs->p2_score) {
    return 0;
  } else if(gs->p1_score < gs->p2_score) {
    return 1;
  } else {
    return 2;
  }
}
