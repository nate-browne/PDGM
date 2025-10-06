#include "pdgm.h"
#include "functions.h"

/**
 * This utility function takes in an unsigned long (a.k.a. uint64_t) and prints it out
 * with commas separating the thousands groupings for better readability.
 */
void fprintfcomma(FILE *stream, uint64_t value) {
    // base case: if the number is smaller than 1,000
    // print it since we don't need a comma anymore
    if(value < 1000) {
      fprintf(stream, "%lu", value);
    } else {
      fprintfcomma(stream, value / 1000);
      fprintf(stream, ",%03lu", value % 1000);
    }
}
