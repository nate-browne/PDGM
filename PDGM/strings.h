#ifndef STRINGS_H
#define STRINGS_H

#define WELCOME_STR "Welcome to %s!\n"
#define GAMES_PROMPT_1 "Enter number of simulations to run (up to "
#define GAMES_PROMPT_2 "; default is 50)\n\tWARNING: excessively large numbers may run _really_ slowly depending on hardware: "

#define ROUND_STR "Round: %u\n"
#define OPP_PREVIOUS_MOVE_STR "Opponent Previous Move: %d\n"

#define REPORT_STR "End of Games Report: %s average score: %lu, %s average score: %lu\n"

#define GAME_STR_1 "\nGame "
#define GAME_STR_2 "\n"

#define ERR_ARGS_NUM_STR "ERROR: Incorrect number of arguments passed.\n"

#define ERRNO_ERR_STR "Error when parsing string into unsigned long: "

#define INVALID_CHAR_ERR_STR "Number \"%s\" contained invalid characters\n"

#define TOO_SMALL_GAME_NO_STR "\nNot enough games selected for a decent sample size. Defaulting to %lu\n"

#endif
