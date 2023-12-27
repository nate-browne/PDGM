#include "pdgm.h"
#include "functions.h"

int32_t calculate_round_number(void) {
  bool is_positive = flip_coin();

  int value = rand() % ROUND_PLUS_MINUS;

  return (is_positive) ? value: -value;
}

/**
 * For this function, heads = true and tails = false
 */
static bool flip_coin(void) {
  int value = rand();

  return value % 2 == 0;
}
