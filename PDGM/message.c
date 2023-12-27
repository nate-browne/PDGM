#include "pdgm.h"
#include "functions.h"

void broadcast_message(char *message) {

  fprintf(stdout, "%s\n", message);
}

char process_incoming_message(char *message) {

  return *message;
}
