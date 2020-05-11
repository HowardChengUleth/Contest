#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
  int sum, a, b;
} Data;

Data A[1000000], B[2000000];

int elem[1000];
int n;

int cmp(const void *a, const void *b)
{
  const Data *x = (const Data *)a, *y = (const Data *)b;

  return x->sum - y->sum;
}

int main(void)
{
  int i, j, jj, k1, k2, d;

  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; i++) {
      scanf("%d", elem+i);
    }
  
    k1 = 0;
    for (i = 0; i < n; i++) {
      for (j = i+1; j < n; j++) {
	A[k1].sum = elem[i] + elem[j];
	A[k1].a = elem[i];
	A[k1++].b = elem[j];
      }
    }
    
    k2 = 0;
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	if (i == j) continue;
	B[k2].sum = elem[i] - elem[j];
	B[k2].a = elem[i];
	B[k2++].b = elem[j];
      }
    }
    
    qsort(A, k1, sizeof(*A), cmp);
    qsort(B, k2, sizeof(*B), cmp);

    i = j = 0;
    d = INT_MIN;
    while (i < k1 && j < k2) {
      if (A[i].sum < B[j].sum) {
	i++;
      } else if (A[i].sum > B[j].sum) {
	j++;
      } else {
	for (jj = 0; j + jj < k2 && B[j+jj].sum == A[i].sum; jj++) {
	  if (A[i].a != B[j+jj].a && A[i].b != B[j+jj].a &&
	      A[i].a != B[j+jj].b && A[i].b != B[j+jj].b &&
	      B[j].a > d) {
	    d = B[j].a;
	  }
	}
	i++;
      }
    }
    if (d > INT_MIN) {
      printf("%d\n", d);
    } else {
      printf("no solution\n");
    }
  }
  return 0;
}
