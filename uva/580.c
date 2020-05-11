#include <stdio.h>

int main(void)
{
  int endL[31], endU[31], endUU[31];
  int n;

  endL[0] = endU[0] = endUU[0] = endUU[1] = 0;
  endL[1] = endU[1] = 1;
  
  
  for (n = 2; n <= 30; n++) {
    endL[n] = endL[n-1] + endU[n-1] + endUU[n-1];
    endU[n] = endL[n-1];
    endUU[n] = endU[n-1];
  }

  while (scanf("%d", &n) == 1 && n > 0) {
    printf("%d\n", (1 << n) - (endL[n] + endU[n] + endUU[n]));
  }

  return 0;
}
