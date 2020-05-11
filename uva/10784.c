#include <stdio.h>
#include <math.h>


int main(void)
{
  long long N, n;
  long double Nld;
  int case_num = 1;

  while (scanf("%lld", &N) == 1 && N) {
    printf("Case %d: ", case_num++);
    Nld = N;
    n = (long long)floor((3 + sqrt(9 + 8*Nld))/2);
    while (n*(n - 3) - 2*N < 0) {
      n++;
    }
    printf("%lld\n", n);
  }
  return 0;
}
