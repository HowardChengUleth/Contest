#include <stdio.h>
#include <stdlib.h>

int n;
int A[10000];

typedef struct {
  int len, chain;
} Chain;

int cmp(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

int chain_cmp(const void *a, const void *b)
{
  const Chain *x = (const Chain *)a, *y = (const Chain *)b;
  
  if (x->chain != y->chain) {
    return x->chain - y->chain;
  } else {
    return x->len - y->len;
  }
}

void solve(void)
{
  Chain chain[10000];
  int chains = 0;
  int i, j;

  for (i = 0; i < n; i = j) {
    for (j = i; j < n && A[j] == A[i]; j++)
      ;
    if (chains <= j-i) {
      chains = j-i;
    }
  }
  
  j = 0;
  for (i = 0; i < n; i++) {
    chain[i].len = A[i];
    chain[i].chain = j;
    j = (j+1) % chains;
  }

  qsort(chain, n, sizeof(*chain), chain_cmp);

  printf("%d\n", chains);
  for (i = 0; i < n; i = j) {
    for (j = i; j < n && chain[j].chain == chain[i].chain; j++) {
      if (j > i) {
	printf(" ");
      }
      printf("%d", chain[j].len);
    }
    printf("\n");
  }
}

int main(void)
{
  int i, first = 1;

  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; i++) {
      scanf("%d", A+i);
    }
    qsort(A, n, sizeof(*A), cmp);
    if (!first) {
      printf("\n");
    }
    solve();
    first = 0;
  }
  return 0;
}
