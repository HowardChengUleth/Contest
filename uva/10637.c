/*
 * Euclidean Algorithm
 *
 * Author: Howard Cheng
 *
 * Given two integers, return their gcd.
 *
 */

#include <stdio.h>
#include <assert.h>

int gcd_table[101][101];

int gcd(int a, int b)
{
  int r;

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  assert(a >= 0);
  return a;
}

void gen_partition(int S, int t, int *partition, int start)
{
  int i, j, good, low;

  if (start == t) {
    if (!S) {
      for (i = 0; i < t-1; i++) {
	printf("%d ", partition[i]);
      }
      printf("%d\n", partition[t-1]);
    }
    return;
  }

  low = (start) ? partition[start-1] : 1;
  if (low > 1) {
    low++;
  }
  if (low * (t-start) > S) {
    return;
  }

  for (i = low; i <= S; i++) {
    good = 1;
    for (j = 0; j < start && good; j++) {
      good = (gcd_table[partition[j]][i] == 1);
    }
    if (good) {
      partition[start] = i;
      gen_partition(S-i, t, partition, start+1);
    }
  }
}

int main(void)
{
  int N, i, j;
  int S, t, partition[30];

  for (i = 0; i <= 100; i++) {
    for (j = 0; j <= 100; j++) {
      gcd_table[i][j] = gcd(i,j);
    }
  }

  scanf("%d", &N);
  for (i = 1; i <= N; i++) {
    scanf("%d %d", &S, &t);
    printf("Case %d:\n", i);

    gen_partition(S, t, partition, 0);
  }
  return 0;
}
