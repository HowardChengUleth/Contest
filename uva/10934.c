#include <stdio.h>

#define MAX_K 100
#define MAX_T 63

unsigned long long height[MAX_K+1][MAX_T+1];

int main(void)
{
  int k, t;
  unsigned long long n;

  for (k = 0; k <= MAX_K; k++) {
    height[k][0] = 0;
  }
  for (t = 1; t <= MAX_T; t++) {
    height[1][t] = t;
    for (k = 2; k <= MAX_K; k++) {
      height[k][t] = height[k-1][t-1] + 1 + height[k][t-1];
    }
  }
    
  while (scanf("%d %llu", &k, &n) == 2 && k) {
    for (t = 1; t <= MAX_T; t++) {
      if (height[k][t] >= n) {
	printf("%d\n", t);
	break;
      }
    }
    if (t > MAX_T) {
      printf("More than 63 trials needed.\n");
    }
  }

  return 0;
}
