#include "pdgm.h"
#include "functions.h"

/**
 * This function calculates the point gains after a particular round.
 * The logic is simple: first we store the move the participants do in the
 * previous move area of the struct, then we use this logic:
 * 
 * both cooperate --> 3 points each
 * one cooperate one defect --> defector gets 5 points cooperator gets 0
 * both defect --> 1 point each
 */
static void process_round_result(GameState_t *gs, const int32_t p1_decision, const int32_t p2_decision) {

  // Store previous moves to report them back to the participants
  gs->p1_previous_move = p1_decision;
  gs->p2_previous_move = p2_decision;

  // Assign point values
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

/**
 * Runs one game. A game consists of some total number of rounds, and for each
 * round we:
 * 
 * 1. tell the participants the round number
 * 2. report the previous move of the opponent (if it's not turn 1)
 * 3. get the move from each participant
 * 4. use `process_round_result` to calculate the scores for this round
 * 
 * Once we've finished all rounds, we report back to the caller to determine which
 * participant is the winner or if it's a tie.
 */
int32_t run_game(GameState_t *gs, ParticipantProc_t *p1, ParticipantProc_t *p2) {

  char buffer[BUFSIZ] = {0};
  int p1_move, p2_move;

  for(uint32_t i = 0; i < gs->total_rounds; ++i) {
    // first, print the round number to the participants (and the console)
    snprintf(buffer, BUFSIZ, ROUND_STR, i + 1);
    fprintf(stdout, "%s", buffer);
    procprint(p1, buffer);
    procprint(p2, buffer);
    memset(buffer, '\0', BUFSIZ);
  
    // next, print the opponent's previous move to the participants
    // only if it's not the first turn
    if(i > 0) {
      snprintf(buffer, BUFSIZ, OPP_PREVIOUS_MOVE_STR, gs->p2_previous_move);
      procprint(p1, buffer);
      memset(buffer, '\0', BUFSIZ);
    
      snprintf(buffer, BUFSIZ, OPP_PREVIOUS_MOVE_STR, gs->p1_previous_move);
      procprint(p2, buffer);
      memset(buffer, '\0', BUFSIZ);
    }
  
    // pull move from each player
    procread(p1, buffer);
    p1_move = atoi(buffer);
    memset(buffer, '\0', BUFSIZ);
  
    procread(p2, buffer);
    p2_move = atoi(buffer);
    memset(buffer, '\0', BUFSIZ);

    process_round_result(gs, p1_move, p2_move);
  }

  // Done with all rounds, determine who won/lost or if a tie occurred
  if(gs->p1_score > gs->p2_score) {
    return P1_WINS;
  } else if(gs->p1_score < gs->p2_score) {
    return P2_WINS;
  } else {
    return TIE;
  }
}
