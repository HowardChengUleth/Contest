/* @JUDGE_ID: 1102NT 100 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cycle_len(int n);
void process(int start, int end);

int main(void)
{
  int n, m;
  int t;

  while (scanf("%d %d", &n, &m) == 2) {
    printf("%d %d ", n, m);
    if (n > m) {
      process(m, n);
    } else {
      process(n, m);
    }
  }
  return 0;

}

int cycle_len(int n)
{
  int count = 0;
  
  while (n != 1) {
    if (n & 0x01) {
      n = 3*n+1;
    } else {
      n >>= 1;
    }
    count++;
  }
  return count+1;
}

void process(int start, int end)
{
  int best;
  int i, t;

  best = -1;
  for (i = start; i <= end; i++) {
    t = cycle_len(i);
    if (t > best) {
      best = t;
    }
  }

  printf("%d\n", best);
}
