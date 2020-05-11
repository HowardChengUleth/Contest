#include <stdio.h>

int num1[1000001], num2[1000001], sum[1000001];

int main(void)
{
  int N, M, i, c, p;

  scanf("%d", &N);
  while (N-- > 0) {
    scanf("%d", &M);
    num1[M] = num2[M] = 0;
    for (i = M-1; i >= 0; i--) {
      scanf("%d %d", num1+i, num2+i);
    }
    c = 0;
    for (i = 0; i <= M; i++) {
      sum[i] = num1[i] + num2[i] + c;
      if (sum[i] >= 10) {
	sum[i] -= 10;
	c = 1;
      } else {
	c = 0;
      }
    }

    p = 0;
    for (i = M; i >= 0; i--) {
      if (sum[i]) {
	p = 1;
      }
      if (p) {
	printf("%d", sum[i]);
      }
    }
    printf("\n");

    if (N) {
      printf("\n");
    }
  }
  return 0;
}
