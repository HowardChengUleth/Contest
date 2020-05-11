#include <stdio.h>
#include <string.h>

char LED[10][7] = {
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1},
  {0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,0,0,0,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1}
};

int N;
char tests[10][8];

int possible(char *test, char *pattern, char *burned)
{
  int i;

  for (i = 0; i < 7; i++) {
    if (test[i] == 'Y' && !pattern[i]) return 0;
    if (test[i] == 'Y' && burned[i]) return 0;
    if (test[i] == 'N' && pattern[i]) {
      burned[i] = 1;
    }
  }
  return 1;

}

int valid(int start)
{
  char burned[7];
  int i;

  memset(burned, 0, 7);
  for (i = 0; i < N; i++) {
    if (!possible(tests[i], LED[start-i], burned)) {
      return 0;
    }
  }
  return 1;
}

int main(void)
{
  int i;
  
  while (scanf("%d", &N) == 1 && N) {
    for (i = 0; i < N; i++) {
      scanf("%s", tests[i]);
    }

    for (i = 9; i >= N-1; i--) {
      if (valid(i)) {
	printf("MATCH\n");
	break;
      }
    }
    if (i < N-1) {
      printf("MISMATCH\n");
    }
  }

  return 0;
}
