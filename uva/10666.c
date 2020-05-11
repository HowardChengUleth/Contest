/* @JUDGE_ID: 1102NT 10666 C "" */

/*
 * Idea: Look at the bit pattern of X.  The k-th round compares the
 * k-th significant bit of X, and if it's 0 then it wins.  So the
 * number of people X definitely beats is 2^k - 1 (not counting himself)
 * if k is the number of 0's from the right (until the first 1).
 * This gives the pessimistic ranking.
 *
 * For optimistic ranking, notice that the only people that can beat
 * X (directly on indirectly) are those whose bit pattern also has k2 > k1
 * 0 bits from the right, where bit k2 is 1 in X.  In other words, the
 * number of people definitely beating X is the Hamming weight of X.
 *
 */

#include <stdio.h>

int opt(int N, int X)
{
  int k = 0;
  while (X) {
    if ((X & 0x01) == 1) {
      k++;
    }
    X >>= 1;
  }
  return k+1;
}

int pess(int N, int X)
{
  int k;

  for (k = 0; k < N && (X & 0x01) == 0; k++) {
    X >>= 1;
  }
  return (1 << N) - (1 << k) + 1;
}

int main(void)
{
  int M, N, X;

  scanf("%d", &M);
  while (M-- > 0) {
    scanf("%d %d", &N, &X);
    printf("%d %d\n", opt(N, X), pess(N, X));
  }
  return 0;
}
