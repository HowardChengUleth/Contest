#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

#define MAX_ELEM 100000

int asc_seq(int A[], int n)
{
  vector<int> last(n+1);
  if (n == 0) {
    return 0;
  }

  int len = 1;
  last[1] = A[0];

  for (int i = 1; i < n; i++) {
    int j = upper_bound(last.begin()+1, last.begin()+len+1, A[i]) -
      last.begin();
    last[j] = A[i];
    len = max(len, j);
  }

  return len;
}

int main(void)
{
  int A[MAX_ELEM];
  int n, test, t, i;

  n = 0;
  test = 1;
  while (scanf("%d", A) == 1 && A[0] != -1) {
    if (test > 1) {
      printf("\n");
    }
    printf("Test #%d:\n", test++);
    n++;
    while (scanf("%d", A+n) == 1 && A[n] != -1) {
      n++;
      assert(n <= MAX_ELEM);
    }
    for (i = 0; i < n/2; i++) {
      t = A[i];
      A[i] = A[n-1-i];
      A[n-1-i] = t;
    }
    printf("  maximum possible interceptions: %d\n", asc_seq(A, n));
    n = 0;
  }
  return 0;
}
