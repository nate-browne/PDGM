#include "pdgm.h"
#include "functions.h"

int main(int argc, char *argv[]) {
  srand(time(NULL));

  char line[BUFSIZ];
  memset(line, '\0', BUFSIZ);

  fprintf(stdout, WELCOME_STR, NAME);
  fprintf(stdout, GAMES_PROMPT);
  fflush(stdout);

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

  GameState_t gs;
  int32_t p1_wins = 0;
  int32_t p2_wins = 0;
  int32_t ties = 0;

  for(int32_t i = 0; i < num_games; ++i) {

    init_game(&gs);
    switch(run_game(&gs)) {
      case 0:
        p1_wins++;
        break;
      case 1:
        p2_wins++;
        break;  
      case 2:
        ties++;
        break;
    }
  }

  char *winner;
  if(p1_wins > p2_wins) {
    winner = "p1";
  } else if(p1_wins < p2_wins) {
    winner = "p2";
  } else {
    winner = "tie";
  }

  fprintf(stdout, RESULTS_STR, p1_wins, p2_wins, ties, winner);
  return EXIT_SUCCESS;
}