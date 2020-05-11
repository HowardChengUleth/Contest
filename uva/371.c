/* @JUDGE_ID: 1102NT 371 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cycle_len(long long n);
void process(int start, int end);

int main(void)
{
  int n, m;

  while (scanf("%d %d", &n, &m) == 2 && (n && m)) {
    if (n > m) {
      process(m, n);
    } else {
      process(n, m);
    }
  }
  return 0;

}

int cycle_len(long long n)
{
  int count = 0;
  
  do {
    if (n & 0x01) {
      n = 3*n+1;
    } else {
      n >>= 1;
    }
    count++;
  } while (n != 1);
  return count;
}

void process(int start, int end)
{
  int best;
  int i, t;
  int best_i;

  best = -1;
  for (i = start; i <= end; i++) {
    t = cycle_len(i);
    if (t > best) {
      best = t;
      best_i = i;
    }
  }

  printf("Between %d and %d, %d generates the longest sequence of "
	 "%d values.\n", start, end, best_i, best);
}
