#include <stdio.h>

int main(void)
{
  int T;
  int i;
  int a, b;
  int sum;

  scanf("%d", &T);
  for (i = 0; i < T; i++) {
    sum = 0;
    printf("Case %d: ", i+1);
    scanf("%d %d", &a, &b);

    while (a <= b) {
      if (a % 2 == 1) {
	sum += a;
      }
      a++;
    }
    printf("%d\n", sum);
  }
  return 0;
}
