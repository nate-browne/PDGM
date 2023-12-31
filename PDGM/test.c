#include "pdgm.h"
#include "functions.h"

#define ASSERT(n) \
if(!(n)) { \
printf("%s - \033[91mFAILED!!\033[0m", #n); \
printf(" on %s ", __DATE__); \
printf("at %s ", __TIME__); \
printf("in file %s ", __FILE__); \
printf("on line %d\n", __LINE__); \
exit(1);}

void test_calculate_round_number(void) {

  srand(time(NULL));
  int t1 = calculate_round_number();
  ASSERT(t1 >= -10)
  ASSERT(t1 <= 10)
}

void test_init_game(void) {
  GameState_t gs;
  init_game(&gs);

  ASSERT(gs.p1_previous_move == NULL);
  ASSERT(gs.p2_previous_move == NULL);
  ASSERT(gs.p1_score == 0);
  ASSERT(gs.p2_score == 0);
  ASSERT(gs.total_rounds >= 190);
  ASSERT(gs.total_rounds <= 210);
}

void test_init_running_count(void) {
  RunningCount_t rc;
  init_running_count(&rc);

  ASSERT(rc.p1_wins == 0);
  ASSERT(rc.p2_wins == 0);
  ASSERT(rc.ties == 0);
}

int main(void) {
  fprintf(stderr, "%s\n", "Starting tests...");
  test_calculate_round_number();
  test_init_game();

  fprintf(stderr, "%s\n", "Tests complete!");
  return EXIT_SUCCESS;
}
