#include <stdio.h>

int main(void)
{
  int n;
  int day = 1;
  char busy[60*24];
  char line[300];
  int s_h, s_m, e_h, e_m;
  int start, end;
  int best_start, best;
  int i, j;

  while (scanf("%d\n", &n) == 1) {
    for (i = 10*60; i < 18*60; i++) {
      busy[i] = 0;
    }
    while (n-- > 0) {
      fgets(line, 300, stdin);
      sscanf(line, "%d:%d %d:%d", &s_h, &s_m, &e_h, &e_m);
      start = s_h*60 + s_m;
      end = e_h*60 + e_m;
      while (start != end) {
	busy[start++] = 1;
      }
    }

    best = 0;
    best_start = -1;
    for (i = 10*60; i < 18*60; i += (j+1)) {
      for (j = 0; i+j < 18*60 && !busy[i+j]; j++)
	;
      if (j > best) {
	best = j;
	best_start = i;
      }
    }

    printf("Day #%d: the longest nap starts at %2d:%02d and will last for ",
	   day++, best_start/60, best_start%60);
    if (best < 60) {
      printf("%d minutes.\n", best);
    } else {
      printf("%d hours and %d minutes.\n", best/60, best%60);
    }
  }
  return 0;
}
