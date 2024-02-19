#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MSGSIZE 4

int main(int argc, char *argv[]) {
  char inbuf[MSGSIZE];

  int p[2];

  pipe(p);
  int pid = fork();

  if (pid == 0) {
    read(p[0], inbuf, MSGSIZE);
    printf("%d: received ping\n", getpid());

    write(p[1], "pong", 4);
    close(p[0]);
    close(p[1]);
    exit(0);
  }
  else {
    write(p[1], "ping", 4);
    close(p[1]);

    read(p[0], inbuf, MSGSIZE);
    close(p[0]);

    printf("%d: received pong\n", getpid());

    exit(0);
  }

  exit(0);
}
