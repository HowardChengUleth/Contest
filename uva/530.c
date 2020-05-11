/* @JUDGE_ID: 1102NT 530 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int count = 0;

unsigned long long binom(unsigned long n, unsigned long m)
{
      long double cnm = 1.0;
      double i, f, t;


      if (m*2 >n) m = n-m;
      for (i=1 ; i <= m; n--, i++)
      {
            f = n;
            t = f/i;
            if (fabs(floor(t)-t) < 1E-9) {
                f /= i;
            } else {
                cnm /= i;
            }
            cnm *= f;
      }
      return floor(cnm+0.5);
}

int main (void) {
    unsigned long n,m;
    while (scanf("%lu %lu", &n, &m) == 2 && (n || m)) {
      printf("%lu\n", binom(n,m));
    }
    return 0;
}
