#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(2, "Usage: sleep second\n");
    exit(1);
  }

  int i = atoi(argv[1]);
  if (i < 0) {
    fprintf(2, "sleep: a non-negetive number is expected.\n");
    exit(1);
  }
  sleep(i);

  exit(0);
}
