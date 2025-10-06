#include "pdgm.h"
#include "functions.h"

/**
 * Hidden function that runs the number of games specified. For each game, we need to initialize the
 * GameState_t struct, run the game (which is some number of rounds), then we increment the RunningCount_t
 * struct based on who won/lost or if a tie occurred.
 */
static void run_games(const uint64_t num_games, GameState_t *gs, RunningCount_t *rc, ParticipantProc_t *pp1, ParticipantProc_t *pp2) {
  for(uint64_t i = 0; i < num_games; ++i) {
    init_game(gs);
    fprintf(stdout, GAME_STR, i + 1); // print which game number we're on to the console
    switch(run_game(gs, pp1, pp2)) {
      case P1_WINS:
        rc->p1_wins++;
        break;
      case P2_WINS:
        rc->p2_wins++;
        break;  
      case TIE:
        rc->ties++;
        break;
    }
  }
}

int main(int argc, char *argv[]) {

  // args should be exe name (argv[0]), participant script 1 (argv[1])
  // and participant scrpit 2 (argv[2])
  if(argc != 3) {
    fprintf(stderr, "ERROR: Incorrect number of arguments passed.\n");
    exit(1);
  }

  // seed the RNG just in case. not necessary really, but doesn't hurt
  srand(time(NULL));

  char line[BUFSIZ] = {0};

  fprintf(stdout, WELCOME_STR, NAME);
  fprintf(stdout, GAMES_PROMPT, UINT64_MAX);
  fflush(stdout);

  // infinite loop to grab the number of games we want to play
  do {

    // If EOF, start over
    if(!fgets(line, BUFSIZ, stdin)) continue;

    // if empty string, just start over
    if(*line == '\n') continue;

    // got something to parse
    break;
  } while(true);

  // find the newline and replace with the null
  line[strcspn(line, "\n")] = '\0';

  // parse the string number into an unsigned long (a.k.a. uint64_t)
  errno = 0;
  char *end;
  uint64_t parsed = strtoul(line, &end, PARSE_BASE); 

  // int value was out of range
  if(errno) {
    perror("Error when parsing string into unsigned long: ");
    exit(1);
  }

  // some other non-parsable character was present (e.g. in "2 hithere", end would point to "hithere")
  if(*end != '\0') {
    fprintf(stderr, "Number \"%s\"contained invalid characters\n", line);
    exit(1);
  }

  uint64_t num_games = DEFAULT_GAME_NUMBER;

  // Need to play at least 50 games.
  if(parsed >= DEFAULT_GAME_NUMBER) {
    num_games = parsed; 
  } else {
    fprintf(stdout, "\nNot enough games selected for a decent sample size. Defaulting to %lu\n", num_games);
  }

  // Fire up participants and initialize the structs
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

  // report back, quit the participants
  fprintf(stdout, RESULTS_STR, pp1->name, rc.p1_wins, pp2->name, rc.p2_wins, rc.ties, winner);
  procprint(pp1, "quit");
  procprint(pp2, "quit");
  destroy_participant_process(pp1, SIGTERM);
  destroy_participant_process(pp2, SIGTERM);

  return EXIT_SUCCESS;
}
