#include <stdio.h>

int count;

void sum(int t, int *x, int index, int n, int last_unused, char *chosen)
{
  int i, printed;

  if (!t) {
    count++;
    printed = 0;
    for (i = 0; i < n; i++) {
      if (chosen[i]) {
	if (printed) {
	  printf("+");
	}
	printf("%d", x[i]);
	printed = 1;
      }
    }
    printf("\n");
    return;
  }
  if (index >= n) {
    return;
  }

  /* try using x[i] if possible */
  if (last_unused != x[index] &&   /* avoid duplicates */
      t >= x[index]) {
    chosen[index] = 1;
    sum(t - x[index], x, index+1, n, last_unused, chosen);
    chosen[index] = 0;
  }

  /* try it without choosing */
  sum(t, x, index+1, n, x[index], chosen);
}

int main(void)
{
  int n, t, x[12];
  char chosen[12];
  int i;

  while (scanf("%d %d", &t, &n) == 2 && n) {
    for (i = 0; i < n; i++) {
      scanf("%d", x+i);
      chosen[i] = 0;
    }
    printf("Sums of %d:\n", t);
    count = 0;
    sum(t, x, 0, n, 10000, chosen);
    if (!count) {
      printf("NONE\n");
    }
  }
  return 0;
}
