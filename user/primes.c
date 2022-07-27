#include "kernel/types.h"
#include "user/user.h"



void
step2(int leftPipe[]) {
  close(leftPipe[1]);
  int prime, num;
  if(read(leftPipe[0], &prime, sizeof(prime))==0){
    close(leftPipe[0]);
    exit(0);
  }
  printf("prime %d\n", prime);
  int rightPipe[2];
  pipe(rightPipe);
  if (fork() == 0) {
    close(leftPipe[0]);
    step2(rightPipe);
  }
  else {
    close(rightPipe[0]);
    while (read(leftPipe[0], &num, sizeof(num)) != 0) {
      if (num % prime != 0) {
        write(rightPipe[1], &num, sizeof(num));
      }
    }
    close(rightPipe[1]);
    close(leftPipe[0]);
    wait(0);
  }
  exit(0);
}



int
main(void) {
  int leftPipe[2];
  pipe(leftPipe);
  if (fork() == 0) {
    step2(leftPipe);
  }
  else {
    close(leftPipe[0]);
    for (int i = 2;i <= 35;i++) {
      write(leftPipe[1], &i, sizeof(i));
    }
    close(leftPipe[1]);
    wait(0);
  }
  exit(0);
}


