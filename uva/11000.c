#include <stdio.h>

/* if m(n) = number of male bees after n years, and
      f(n) = number of female bees after n years, then we have

   f(0) = 1
   m(0) = 0

   f(n) = m(n-1) + 1
   m(n) = m(n-1) + f(n-1)

   Note that f(n) = m(n-1) + 1 = m(n-2) + f(n-2) + 1 = f(n-1) + f(n-2),
   so f(n) is the fibonacci sequence.  This means it grows quickly and
   we don't have to worry about evaluating it for large n.
*/

int main(void)
{
  int n;
  long long m, f, newm, newf;
  int i;

  while (scanf("%d", &n) == 1 && n != -1) {
    f = 1;
    m = 0;
    for (i = 0; i < n; i++) {
      newf = m + 1;
      newm = m + f;
      f = newf;
      m = newm;
    }
    printf("%lld %lld\n", m, f+m);
  }

  return 0;
}
