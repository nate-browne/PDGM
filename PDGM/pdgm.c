#include "pdgm.h"
#include "functions.h"

static void run_games(const uint64_t num_games, GameState_t *gs, RunningCount_t *rc, ParticipantProc_t *pp1, ParticipantProc_t *pp2) {
  for(uint64_t i = 0; i < num_games; ++i) {
    init_game(gs);
    switch(run_game(gs, pp1, pp2)) {
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

int main(int argc, char *argv[]) {

  if(argc != 3) {
    fprintf(stderr, "ERROR: Incorrect number of arguments passed.\n");
    exit(1);
  }

  srand(time(NULL));

  char line[BUFSIZ] = {0};

  fprintf(stdout, WELCOME_STR, NAME);

  fprintf(stdout, GAMES_PROMPT, UINT64_MAX);
  fflush(stdout);
  memset(line, '\0', BUFSIZ);

  while(true) {

    if(!fgets(line, BUFSIZ, stdin)) continue;
    if(*line == '\n') continue;
    break;
  }

  // find the newline and replace with the null
  line[strcspn(line, "\n")] = '\0';

  // parse the string number into an unsigned long (a.k.a. uint64_t)
  errno = 0;
  char *end;
  uint64_t parsed = strtoul(line, &end, 10); 
  if(errno) {
    perror("Error when parsing string into unsigned long");
  }

  if(*end != '\0') {
    fprintf(stderr, "Number contained invalid characters\n");
    exit(1);
  }


  uint64_t num_games = DEFAULT_GAME_NUMBER;

  if(parsed >= DEFAULT_GAME_NUMBER) {
    num_games = parsed; 
  } else {
    fprintf(stdout, "\nNot enough games selected for a decent sample size. Defaulting to %lu\n", num_games);
  }

  ParticipantProc_t *pp1 = start_participant_process(argv[FIRST_PARTICIPANT]);
  ParticipantProc_t *pp2 = start_participant_process(argv[SECOND_PARTICIPANT]);

  RunningCount_t rc;
  init_running_count(&rc);

  GameState_t gs;

  run_games(num_games, &gs, &rc, pp1, pp2);

  char *winner;
  if((rc.p1_wins > rc.p2_wins) && (rc.p1_wins > rc.ties)) {
    winner = pp1->name;
  } else if((rc.p1_wins < rc.p2_wins) && (rc.p2_wins > rc.ties)) {
    winner = pp2->name;
  } else {
    winner = "tie";
  }

  fprintf(stdout, RESULTS_STR, pp1->name, rc.p1_wins, pp2->name, rc.p2_wins, rc.ties, winner);
  procprint(pp1, "quit");
  procprint(pp2, "quit");
  destroy_participant_process(pp1, SIGTERM);
  destroy_participant_process(pp2, SIGTERM);

  return EXIT_SUCCESS;
}
