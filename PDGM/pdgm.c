#include "pdgm.h"
#include "functions.h"

/**
 * Hidden function that runs the number of games specified. For each game, we need to initialize the
 * GameState_t struct, run the game (which is some number of rounds), then we update the scores in the running count
 * struct.
 */
static void run_games(const uint64_t num_games, GameState_t *gs, RunningCount_t *rc, ParticipantProc_t *pp1, ParticipantProc_t *pp2) {
  for(uint64_t i = 0; i < num_games; ++i) {
    init_game(gs);

    // print which game number we're on to the console
    fprintf(stdout, GAME_STR_1); 
    fprintfcomma(stdout, i + 1);
    fprintf(stdout, GAME_STR_2);
    fprintf(stdout, "%s\n\n", "*****************");

    run_game(gs, pp1, pp2);
    rc->p1_scores[i] = gs->p1_score;
    rc->p2_scores[i] = gs->p2_score;
  }
}

/**
 * Calculate the average score across all of the games for a given participant
 */
static uint64_t calc_average_score(uint64_t *scores, uint64_t num_games) {
  uint64_t total = 0; 
  for(uint64_t i = 0; i < num_games; ++i) {
    total += scores[i];
  }
  return total / num_games;
}

int main(int argc, char *argv[]) {

  // args should be exe name (argv[0]), participant script 1 (argv[1])
  // and participant scrpit 2 (argv[2])
  if(argc != 3) {
    fprintf(stderr, ERR_ARGS_NUM_STR);
    exit(1);
  }

  // seed the RNG just in case. not necessary really, but doesn't hurt
  srand(time(NULL));

  char line[BUFSIZ] = {0};

  fprintf(stdout, WELCOME_STR, NAME);
  fprintf(stdout, GAMES_PROMPT_1);
  fprintfcomma(stdout, UINT64_MAX);
  fprintf(stdout, GAMES_PROMPT_2);
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

  /* parse the string number into an unsigned long (a.k.a. uint64_t) */

  errno = 0;
  char *end;
  uint64_t parsed = strtoul(line, &end, PARSE_BASE); 

  // Error #1: int value was out of range
  if(errno) {
    perror(ERRNO_ERR_STR);
    exit(1);
  }

  // Error #2: some other non-parsable character was present
  // (e.g. in "2 hithere", end would point to "hithere")
  if(*end != '\0') {
    fprintf(stderr, INVALID_CHAR_ERR_STR, line);
    exit(1);
  }

  uint64_t num_games = DEFAULT_GAME_NUMBER;

  // Need to play at least 50 games.
  if(parsed >= DEFAULT_GAME_NUMBER) {
    num_games = parsed; 
  } else {
    fprintf(stdout, TOO_SMALL_GAME_NO_STR, num_games);
  }

  /* Fire up participants and initialize the structs */

  ParticipantProc_t *pp1 = start_participant_process(argv[FIRST_PARTICIPANT]);
  ParticipantProc_t *pp2 = start_participant_process(argv[SECOND_PARTICIPANT]);

  RunningCount_t rc;
  init_running_count(&rc, num_games);

  GameState_t gs;

  run_games(num_games, &gs, &rc, pp1, pp2);

  /* report results */

  uint64_t p1_avg_score = calc_average_score(rc.p1_scores, num_games);
  uint64_t p2_avg_score = calc_average_score(rc.p2_scores, num_games);

  fprintf(stdout, REPORT_STR, pp1->name, p1_avg_score, pp2->name, p2_avg_score);

  /* cleanup and exit */

  free(rc.p1_scores);
  free(rc.p2_scores);

  procprint(pp1, "quit");
  procprint(pp2, "quit");
  destroy_participant_process(pp1, SIGTERM);
  destroy_participant_process(pp2, SIGTERM);

  return EXIT_SUCCESS;
}
