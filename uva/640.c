/* @JUDGE_ID: 1102NT 640 C "" */

#include <stdio.h>

char used[10000001];

int next(int n)
{
  int t = n;
  while (n) {
    t += n % 10;
    n /= 10;
  }
  return t;
}

int main(void)
{
  int n, n2;

  for (n = 1; n <= 1000000; n++) {
    if (!used[n]) {
      printf("%d\n", n);
    }
    for (n2 = next(n); n2 <= 1000000 && !used[n2]; n2 = next(n2)) {
      used[n2] = 1;
    }
  }
  return 0;


}
