/* @JUDGE_ID: 1102NT 10202 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_N 9
int sum[MAX_N*(MAX_N-1)/2];
int n, N;

int cmp(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

int read_case(void)
{
  int i;

  if (scanf("%d", &n) == 1) {
    N = n*(n-1)/2;
    for (i = 0; i < N; i++) {
      scanf("%d", sum+i);
    }
    return 1;
  } else {
    return 0;
  }
}

int try(int smallest)
{
  int A[MAX_N], i, j, k, index;
  char marked[MAX_N*(MAX_N-1)/2];
  
  memset(marked, 0, N);

  A[0] = smallest;
  
  /* if we know the smallest, then sum[0] must be A[0]+A[1], and
     sum[1] must be A[0]+A[2]...

     The next sum is either A[0]+A[3] or A[1]+A[2].  But we already
     know A[1]+A[2] so we can remove it.  The next smallest one is
     A[0]+A[3].

     In general, every time we determine an extra element of A, we
     can wipe out the sums it makes with all previous elements.
     The next element must be A[0]+A[k].
 */

  for (i = 1; i < n; i++) {
    for (index = 0; index < N && marked[index]; index++)
      ;
    assert(index < N);
    A[i] = sum[index] - A[0];
    for (j = 0; j < i; j++) {
      for (k = 0; k < N && (sum[k] != A[j]+A[i] || marked[k]); k++)
	;
      if (k >= N) {
	/* no matching sum, bad */
	return 0;
      }
      marked[k] = 1;
    }
  }

  for (i = 0; i < n; i++) {
    printf("%d%s", A[i], (i < n-1) ? " " : "\n");
  }
  return 1;
}

void solve_case(void)
{
  int j;

  /* we know that

     A[0] = ((A[0]+A[1]) + (A[0]+A[2]) - (A[1]+A[2]))/2
          = (sum[0] + sum[1] - sum[j]) / 2      (for some j > 1)

     so we just try all j
  */

  for (j = 2; j < N; j++) {
    /* technically we should only do this if sum[0]+sum[1]+sum[j] is even */
    /* but it doesn't hurt to try it anyway.                              */
    if (try((sum[0]+sum[1]-sum[j])/2)) {
      return;
    }
  }
  printf("Impossible\n");
}

int main(void)
{
   while (read_case()) {
     qsort(sum, N, sizeof(*sum), cmp);
     solve_case();
   }
   return 0;
}
