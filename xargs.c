#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(2, "Usage: xargs <command> [argv...]\n");
    exit(1);
  }

  char buf[512];
  char c;
  char *params[MAXARG];
  int offset = 0;
  int flag = 0;


  int i;
  for (i = 0; i < argc - 1; ++i) {
    params[i] = argv[i+1];
  }
  params[i] = 0;

  while ((flag = read(0, &c, sizeof(char))) > 0) {
    if (c == '\n') {
        params[i] = buf;
        
        int pid = fork();
        if (pid < 0) {
            exit(1);
        }
        else if (pid == 0) {
            exec(params[0], params);
        }
        else {
            wait(0);
        }

        memset(buf, 0, sizeof(buf));
        offset = 0;
    }
    else {
        buf[offset] = c;
        ++offset;
    }
      
  }
  exit(0);

}