/* @JUDGE_ID: 1102NT 356 C "" */

#include <stdio.h>

int seg, inside, n;

int incircle(int i, int j)
{
  return (4*(i*i+j*j) <= 4*n*n - 4*n + 1);
}

void count(int i, int j)
{
  int in = 0;

  in = incircle(i, j) + incircle(i, j+1) + incircle(i+1, j) + 
       incircle(i+1, j+1);
  if (in == 4) {
    inside += 4;
  } else if (in > 0) {
    seg += 4;
  }
}

int main(void)
{
  int i, j;
  int first = 1;

  while (scanf("%d", &n) == 1) {
    seg = inside = 0;
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	count(i, j);
      }
    }
    if (!first) {
      printf("\n");
    }
    first = 0;
    printf("In the case n = %d, %d cells contain segments of the circle.\n",
	   n, seg);
    printf("There are %d cells completely contained in the circle.\n", inside);
  }

  return 0;
}
