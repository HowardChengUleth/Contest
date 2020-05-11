#include <stdio.h>

#define MAX_N 50

void solve_case(int n)
{
  int cards[MAX_N];
  int i, k, t;

  for (i = 0; i < n; i++) {
    cards[i] = i+1;
  }

  printf("Discarded cards:");
  if (n > 1) {
    printf(" ");
  }
  for (k = 0; k < n-1; k++) {
    printf("%s%d", (k ? ", " : ""), cards[k]);
    t = cards[k+1];
    for (i = k+1; i < n-1; i++) {
      cards[i] = cards[i+1];
    }
    cards[n-1] = t;
  }
  printf("\nRemaining card: %d\n", cards[n-1]);
}

int main(void)
{
  int n;

  while (scanf("%d", &n) == 1 && n) {
    solve_case(n);
  }
  return 0;
}
