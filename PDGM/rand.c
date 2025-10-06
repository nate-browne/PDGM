#include "pdgm.h"
#include "functions.h"

/**
 * For this function, heads = true and tails = false
 */
static bool flip_coin(void) {
  return rand() % 2 == 0;
}

/**
 * Calculate a modifier for the number of rounds.
 * The base number is 200, and this function generates a positive
 * or negative number in the range (-11,11) for the number of rounds
 * to be played.
 */
int32_t calculate_round_number(void) {
  int32_t value = rand() % ROUND_PLUS_MINUS;
  return (flip_coin()) ? value : -value;
}
