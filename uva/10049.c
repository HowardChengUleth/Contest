/* @JUDGE_ID: 1102NT 10049 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 1000001
int g[MAX_SIZE];
int g_size;

int f(int n)
{
  int lo = 1, hi = g_size+1;
  int mid;

  while (hi - lo > 1) {
    mid = (lo + hi)/2;
    if (g[mid] <= n) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  assert(g[lo] <= n && (lo == g_size || n < g[lo+1]));
  return lo;
}

int main(void)
{
  int n;

  /* compute the g's */
  g[1] = 1;
  g[2] = 2;
  g[3] = 4;
  g_size = 3;
  while (g[g_size] < 2000000000) {
    g[g_size+1] = g[g_size] + f(g_size);
    g_size++;
  }
  while (scanf("%d", &n) == 1 && n) {
    printf("%d\n", f(n));
  }
  return 0;
}
