#include <stdio.h>

void process_block(int N)
{
  int perm[1000];
  int stack[1000];
  int i, ssize, in;
  int done, bad;

  while (scanf("%d", perm) == 1 && perm[0]) {
    for (i = 1; i < N; i++) {
      scanf("%d", perm+i);
    }
    ssize = 0;

    in = 1;
    
    bad = 0;
    for (i = 0; i < N && !bad; i++) {
      done = 0;
      while (!done && !bad) {
	if (ssize > 0 && stack[ssize-1] == perm[i]) {
	  ssize--;
	  done = 1;
	} else if (perm[i] >= in) {
	  stack[ssize++] = in++;
	} else {
	  bad = 1;
	}
      }
    }
    printf("%s\n", (bad ? "No" : "Yes"));
  }
}

int main(void)
{
  int N;

  while (scanf("%d", &N) == 1 && N > 0) {
    process_block(N);
    printf("\n");
  }
  return 0;
}
