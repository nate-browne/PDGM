#include "pdgm.h"
#include "functions.h"

static void run_games(const int32_t num_games, GameState_t *gs, RunningCount_t *rc) {
  for(int32_t i = 0; i < num_games; ++i) {

    init_game(gs);
    switch(run_game(gs)) {
      case 0:
        rc->p1_wins++;
        break;
      case 1:
        rc->p2_wins++;
        break;  
      case 2:
        rc->ties++;
        break;
    }
  }
}

int main(void) {
  srand(time(NULL));

  char line[BUFSIZ];
  memset(line, '\0', BUFSIZ);

  fprintf(stdout, WELCOME_STR, NAME);

  bool repeat = false;

  do {
    fprintf(stdout, GAMES_PROMPT);
    fflush(stdout);
    memset(line, '\0', BUFSIZ);

    while(true) {

      if(!fgets(line, BUFSIZ, stdin)) continue;
      if(*line == '\n') continue;
      break;
    }

    int parsed = atoi(line);
    int32_t num_games = DEFAULT_GAME_NUMBER;

    if(parsed > DEFAULT_GAME_NUMBER) {
      num_games = parsed; 
    }

    RunningCount_t rc;
    init_running_count(&rc);

    GameState_t gs;

    run_games(num_games, &gs, &rc);

    char *winner;
    if(rc.p1_wins > rc.p2_wins) {
      winner = "p1";
    } else if(rc.p1_wins < rc.p2_wins) {
      winner = "p2";
    } else {
      winner = "tie";
    }

    fprintf(stdout, RESULTS_STR, rc.p1_wins, rc.p2_wins, rc.ties, winner);

    memset(line, '\0', BUFSIZ);
    fprintf(stdout, REPEAT_STR);
    fflush(stdout);

    if(!fgets(line, BUFSIZ, stdin)) repeat = false;
    if(toupper(*line) == 'Y') repeat = true;
  } while(repeat);

  return EXIT_SUCCESS;
}
