/* @JUDGE_ID: 1102NT 524 C "" */

#include <stdio.h>

char table[17][17];

int isprime(int n)
{
  int p;

  if (n % 2 == 0) {
    return 0;
  }
  for (p = 3; p*p <= n; p += 2) {
    if (n % p == 0) {
      return 0;
    }
  }
  return 1;
}

void search(int *perm, int n, int i)
{
  int k, t;
  if (i == n) {
    if (table[perm[n-1]][perm[0]]) {
      for (k = 0; k < n; k++) {
	printf("%d%s", perm[k], (k == n-1) ? "\n" : " ");
      }
    }
    return;
  }
  for (k = i; k < n; k++) {
    if (table[perm[i]][perm[i-1]]) {
      search(perm, n, i+1);
    }
    if (k < n-1) {
      t = perm[i];
      perm[i] = perm[k+1];
      perm[k+1] = t;
    }
  }
  t = perm[i];
  for (k = i; k < n-1; k++) {
    perm[k] = perm[k+1];
  }
  perm[n-1] = t;
}

int main(void)
{
  int n;
  int cases = 0;
  int perm[16], i, j;

  for (i = 1; i <= 16; i++) {
    for (j = 1; j <= 16; j++) {
      table[i][j] = isprime(i + j);
    }
  }

  while (scanf("%d", &n) == 1) {
    if (cases > 0) {
      printf("\n");
    }
    printf("Case %d:\n", ++cases);
    for (i = 0; i < n; i++) {
      perm[i] = i+1;
    }
    search(perm, n, 1);
  }
  return 0;
}
