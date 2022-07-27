#include "kernel/types.h"
#include "user/user.h"

int
main(void) {
  char buffer[512];
  int p1[2];//parent process in and child process out
  int p2[2];//child process in and parent process out
  pipe(p1);
  pipe(p2);
  if (fork() == 0) {//child process
    close(p1[0]);
    close(p2[1]);
    read(p2[0], buffer, sizeof(buffer));
    printf("%d: received ping\n", getpid());
    write(p1[1], buffer, sizeof(buffer));
    close(p1[1]);
    close(p2[0]);
  }
  else {//parent process
    close(p1[1]);
    close(p2[0]);
    write(p2[1], "This is a byte.\n", 17);
    read(p1[0], buffer, sizeof(buffer));
    printf("%d: received pong\n", getpid());
    close(p2[1]);
    close(p1[0]);
  }

  exit(0);
}
