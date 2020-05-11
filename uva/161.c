#include <stdio.h>

int lights[100];
int n;

int read_case(void)
{
  int d;

  n = 0;

  scanf("%d", &lights[n++]);
  scanf("%d", &lights[n++]);
  while (scanf("%d", &d) && d) {
    lights[n++] = d;
  }
  return !(n == 2 && !lights[0] && !lights[1]);
}

void solve_case(void)
{
  char green[5*60*60+1];
  int i, j, k;
  int first;

  for (i = 0; i <= 5*60*60; i++) {
    green[i] = 1;
  }

  for (i = 0; i < n; i++) {
    j = 0;
    while (j <= 5*60*60) {
      j += lights[i] - 5;
      for (k = 0; k < 5+lights[i] && j <= 5*60*60; k++, j++) {
	green[j] = 0;
      }
    }
  }

  first = 1;
  for (i = 0; i <= 5*60*60; i++) {
    if (first && !green[i]) {
      first = 0;
    } else if (!first && green[i]) {
      printf("%02d:%02d:%02d\n", i/3600, (i/60)%60, i%60);
      return;
    }
  }
  printf("Signals fail to synchronise in 5 hours\n");

}

int main(void)
{
  while (read_case()) {
    solve_case();
  }
  return 0;
}
