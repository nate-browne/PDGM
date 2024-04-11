#include "pdgm.h"
#include "functions.h"

static void set_up_child_IO(int to_prog[2], int from_prog[2]) {
  signal(SIGPIPE, SIG_IGN);
  pipe(to_prog);
  pipe(from_prog);
}

ParticipantProc_t * start_participant_process(char *exe_name) {
  int pid;
  int to_prog[2], from_prog[2];
  char buf[BUFSIZ];

  set_up_child_IO(to_prog, from_prog);

  if((pid = fork()) == 0) {
    // close the unused pipe ends
    close(to_prog[1]);
    close(from_prog[0]);

    dup2(to_prog[0], 0);
    dup2(from_prog[1], 1);

    if(to_prog[0] >= 2) close(to_prog[0]); // if this is 0 or 1, dup2 closed the original
    close(from_prog[1]);                   // and closing again loses one of the pipes

    if(fileno(stderr) >= 2) {
      dup2(1, fileno(stderr)); // force stderr into the pipe
    }

    char *arguments[2];
    arguments[0] = exe_name;
    arguments[1] = NULL;
    execvp(exe_name, arguments);
  
    // if we get to this point, exec failed
    perror(exe_name);
    exit(1);
  }

  // close parent process fds
  close(to_prog[0]);
  close(from_prog[1]);

  ParticipantProc_t *pp = calloc(1, sizeof(ParticipantProc_t));
  pp->pid = pid;
  pp->fd_from = from_prog[0];
  pp->fd_to = to_prog[1];
  pp->in = fdopen(pp->fd_from, "r");
  pp->out = fdopen(pp->fd_to, "w");
  pp->name = exe_name;
  return pp;
}

void destroy_participant_process(ParticipantProc_t *pp, int signal_type) {
  if(signal_type & 1) {
    kill(pp->pid, signal_type == 9 ? SIGKILL : SIGTERM); // 9 send the "hard-kill" option
  }

  wait((int *)0);
  fclose(pp->in);
  fclose(pp->out);
  close(pp->fd_from);
  close(pp->fd_to);
  free(pp);
}

void procprint(FILE* out, char *msg) {
  fprintf(out, "%s\n", msg);
}

void procread(ParticipantProc_t *pp, char *buffer) {
  fread(buffer, sizeof(char), BUFSIZ, pp->in);
}
