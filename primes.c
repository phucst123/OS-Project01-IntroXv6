#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child_process(int p[2]) {
  close(p[1]);

  int prime;

  if (read(p[0], &prime, sizeof(int)) == 0)
    exit(0);
  
  printf("prime %d\n", prime);

  int new_p[2];

  pipe(new_p);

  if (fork() == 0)
    child_process(new_p);
  else {
    int n;
    while (read(p[0], &n, sizeof(int))) {
      if (n % prime != 0)
        write(new_p[1], &n, sizeof(int));      
    }
    close(new_p[1]);
  }
}

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);

  if (fork() == 0)
    child_process(p);
  else {
    close(p[0]);
    int i;
    for (i = 2; i <= 35; ++i) {
      write(p[1], &i, sizeof(int));
    }
    close(p[1]);
  }
  wait(0);
  exit(0);
}
