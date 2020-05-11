#include <stdio.h>
#include <assert.h>


int gcd(int a, int b)
{
  int r;

  /* unnecessary if a, b >= 0 */
  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  assert(a >= 0);
  return a;
}

int G(int N)
{
  int S = 0;
  int i, j;

  for (i = 1; i < N; i++) {
    for (j = i+1; j <= N; j++) {
      S += gcd(i, j);
    }
  }
  return S;
}

int main(void)
{
  int n;

  while (scanf("%d", &n) == 1 && n) {
    printf("%d\n", G(n));
  }


  return 0;
}
