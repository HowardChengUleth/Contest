/*
 * See:
 *
 * http://stason.org/TULARC/self-growth/puzzles/200-geometry-tiling-count-1x2-p.html
 *
 */

#include <stdio.h>
#include <math.h>

#define MAX_N 100

unsigned long long count(int M, int N)
{
  int m, n;
  long double prod = 1;
  long double pi = acosl(-1.0);
  long double t;

  if (M*N % 2 != 0) {
    return 0;
  }
  for (m = 1; m <= M; m++) {
    for (n = 1; n <= N; n++) {
      t = cosl(m*pi/(M+1))*cosl(m*pi/(M+1));
      t += cosl(n*pi/(N+1))*cosl(n*pi/(N+1));
      t = powl(t, 0.25);
      prod *= t;
    }
  }
  prod *= powl(2, M*N/2.0);
  return floorl(prod + 0.5);
}

int main(void)
{
  int m, n;

  for (m = 1; m <= MAX_N; m++) {
    for (n = 1; n <= MAX_N; n++) {
      if (m * n > MAX_N) continue;
      printf("  ans[%d][%d] = %lluLLU;\n", m, n, count(m, n));
    }
  }

  return 0;
}
