/* @JUDGE_ID: 1102NT 374 C "" */

#include <stdio.h>
#include <assert.h>

void fast_exp(int b, int n, int m)
{
  int res = 1;
  int x = b;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res = (res * x) % m;
    } else {
      n >>= 1;
      x = (x * x) % m;
    }
  }

  printf("%d\n", (int)res);
}

int main(void)
{
  int b, n, m;

  while (scanf("%d %d %d", &b, &n, &m) == 3) {
    fast_exp(b % m, n, m);
  }
  return 0;
  
}
