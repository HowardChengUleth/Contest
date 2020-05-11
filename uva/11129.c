#include <stdio.h>

#define MAX_N 10000

void gen(int *seq, int start, int n)
{
  int i, first;

  if (n == 1) {
    seq[start] = 0;
    return;
  }

  first = n/2 + n%2;
  gen(seq, start, first);
  for (i = 0; i < first; i++) {
    seq[start+i] *= 2;
  }

  start += first;
  n -= first;
  gen(seq, start, n);
  for (i = 0; i < n; i++) {
    seq[start+i] = seq[start+i]*2+1;
  }
}

int main(void)
{
  int seq[MAX_N];
  int n, i;

  while (scanf("%d", &n) == 1 && n) {
    gen(seq, 0, n);
    printf("%d:", n);
    for (i = 0; i < n; i++) {
      printf(" %d", seq[i]);
    }
    printf("\n");
  }

  return 0;
}
