#include <stdio.h>

int main(void)
{
  long long N, num, sum, line;
  
  while (scanf("%lld", &N) == 1) {
    line = (N+1)/2;
    num = line*line;
    sum = 6*num-9;
    printf("%lld\n", sum);
  }


  return 0;
}
