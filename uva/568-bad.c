/* @JUDGE_ID: 1102NT 568 C "" */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int last(int n)
{
  while (n % 10 == 0) {
    n /= 10;
  }
  return n % 100000;

}

int main(void)
{
  int n;
  int i, d;

  while (scanf("%d", &n) == 1) {
    for (i = d = 1; i <= n; i++) {
      d = last(d * i);
    }
    printf("%5d -> %d\n", n, d % 10);
  }
  return 0;
}
