#include <stdio.h>
#include <math.h>

int main(void)
{
  long long N;

  while (scanf("%lld", &N) == 1 && N > 0) {
    if (N == 1) {
      printf("0%%\n");
    } else {
      printf("%lld%%\n", N*25);
    }
  }

  return 0;
}
