#include <stdio.h>

#define MAX_N 1000000

/* this is a slight modification of merge sort to count inversions at
   the same time */
long long inversions(int *A, int n)
{
  static int temp[MAX_N];
  int mid;
  long long left, right, count;
  int i, j, k;

  if (n <= 1) {
    return 0;
  }

  mid = n/2;
  left = inversions(A, mid);
  right = inversions(A+mid, n-mid);

  count = 0;
  k = i = 0;
  j = mid;

  while (i < mid && j < n) {
    if (A[i] <= A[j]) {
      temp[k++] = A[i++];
    } else {
      temp[k++] = A[j++];
      count += mid - i;
    }
  }
  while (i < mid) {
    temp[k++] = A[i++];
  }
  while (j < n) {
    temp[k++] = A[j++];
  }
  for (i = 0; i < n; i++) {
    A[i] = temp[i];
  }

  return left + right + count;
}

int A[MAX_N];

int main(void)
{
  int n, i;

  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; i++) {
      scanf("%d", A+i);
    }
    printf("%lld\n", inversions(A, n));
  }
  return 0;
}
