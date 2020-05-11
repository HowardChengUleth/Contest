#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int W, S, index;
} Elephant;

int cmp(const void *a, const void *b)
{
  Elephant *x = (Elephant *)a, *y = (Elephant *)b;
  return y->S - x->S;
}

void print(Elephant *A, int *pred, int index)
{
  if (index == -1) {
    return;
  }
  print(A, pred, pred[index]);
  printf("%d\n", A[index].index);
}

int main(void)
{
  Elephant A[1001];
  int len[1000], pred[1000];
  int n = 0;
  int i, j, best, best_i;

  while (scanf("%d %d", &A[n].W, &A[n].S) == 2) {
    A[n].index = n+1;
    n++;
  }

  qsort(A, n, sizeof(*A), cmp);

  best = 1;
  best_i = 0;
  for (i = 0; i < n; i++) {
    pred[i] = -1;
    len[i] = 1;

    for (j = 0; j < i; j++) {
      if (A[j].W < A[i].W && A[j].S > A[i].S) {
	if (len[j]+1 > len[i]) {
	  len[i] = len[j]+1;
	  pred[i] = j;
	}
      }
    }
    if (len[i] > best) {
      best = len[i];
      best_i = i;
    }
  }
  printf("%d\n", best);
  print(A, pred, best_i);




  return 0;
}
