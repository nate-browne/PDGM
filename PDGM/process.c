#include "pdgm.h"
#include "functions.h"

/**
 * Internal function that take in the file descriptors for the
 * child process and creates the pipes for them. This allows
 * us to capture `stdin` and `stdout` for the participants
 */
static void set_up_child_IO(int to_prog[2], int from_prog[2]) {
  signal(SIGPIPE, SIG_IGN);

  if(pipe(to_prog)) {
    fprintf(stderr, "Error setting up program pipe.\n");
    exit(1);
  }

  if(pipe(from_prog)) {
    fprintf(stderr, "Error setting up program pipe.\n");
    exit(1);
  }
}

/**
 * Takes in the path to a participant executable and starts it up.
 * Uses the fork-exec paradigm where we fork off a new process
 * and in that process we start the participant executable to keep
 * the current process (and therefore current program) running.
 */
ParticipantProc_t * start_participant_process(char *exe_path) {
  int pid;
  int to_prog[2], from_prog[2];

  // set up `stdin` and `stdout` for the child process
  set_up_child_IO(to_prog, from_prog);

  // fork off a new process first
  if((pid = fork()) == 0) {
    // close the unused pipe ends
    close(to_prog[1]);
    close(from_prog[0]);

    // turn our pipe into the process' stdin
    dup2(to_prog[0], 0);

    // turn our pipe into the process' stdout
    dup2(from_prog[1], 1);

    // if this is 0 or 1, dup2 closed the original
    if(to_prog[0] >= 2) {
      close(to_prog[0]);
    }

    // and closing again loses one of the pipes
    close(from_prog[1]);

    // force stderr into the pipe as well
    if(fileno(stderr) >= 2) {
      dup2(1, fileno(stderr));
    }

    // set up the new process and start it
    char *arguments[2];
    arguments[0] = exe_path;
    arguments[1] = NULL; // no command-line arguments are passed to the participants
    execvp(exe_path, arguments);
  
    // if we get to this point, exec failed
    perror(exe_path);
    exit(1);
  }

  // close parent process fds
  close(to_prog[0]);
  close(from_prog[1]);

  // initialize the struct and return it
  ParticipantProc_t *pp = calloc(1, sizeof(ParticipantProc_t));
  pp->pid = pid;
  pp->fd_from = from_prog[0];
  pp->fd_to = to_prog[1];
  pp->in = fdopen(pp->fd_from, "r");
  pp->out = fdopen(pp->fd_to, "w");
  pp->name = exe_path;
  return pp;
}

/**
 * Takes a participant process pointer and ends it using the given
 * `signal_type`
 */
void destroy_participant_process(ParticipantProc_t *pp, int signal_type) {
  if(signal_type & 1) {
    kill(pp->pid, signal_type == 9 ? SIGKILL : SIGTERM); // 9 send the "hard-kill" option
  }

  // wait for the child process to die, then close all file descriptors,
  // file pointers, and free the allocated heap memory
  wait((int *)0);
  fclose(pp->in);
  fclose(pp->out);
  close(pp->fd_from);
  close(pp->fd_to);
  free(pp);
}

/**
 * Function to print messages out to a participant.
 */
void procprint(ParticipantProc_t *pp, const char *msg) {
  fprintf(pp->out, "%s", msg);
  fflush(pp->out);
}

/**
 * Function to read from a participant.
 */
void procread(ParticipantProc_t *pp, char *buffer) {
  if(!fgets(buffer, BUFSIZ, pp->in)) {
    fprintf(stderr, "failed to read from participant process %s\n", pp->name);
    exit(1);
  }
}
