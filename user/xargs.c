#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"


int
main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(2, "Usage: xargs <command>\n");
    exit(1);
  }

  char* argConcat[MAXARG];
  int argCnt = argc - 1;
  for (int i = 1;i < argc;i++) {
    argConcat[i - 1] = argv[i];
  }
  char buffer[MAXARG];
  int count = 0;
  char curChar;
  while (read(0, &curChar, sizeof(curChar)) != 0) {
    if (curChar == '\n') {
      buffer[count] = 0;
      argConcat[argCnt++] = buffer;
      argConcat[argCnt] = 0;
      if (fork() == 0) {
        exec(argv[1], argConcat);
        exit(0);
      }
      wait(0);
      argCnt--;
      count = 0;
    }
    else {
      buffer[count++] = curChar;
    }
  }
  exit(0);
}
