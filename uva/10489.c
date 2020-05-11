#include <stdio.h>

int main(void)
{
  int T, N, B, K, a;
  int ans, temp;

  scanf("%d", &T);
  while (T-- > 0) {
    scanf("%d %d", &N, &B);
    ans = 0;
    while (B-- > 0) {
      scanf("%d", &K);
      temp = 1;
      while (K-- > 0) {
	scanf("%d", &a);
	temp = (temp*a) % N;
      }
      ans = (ans + temp) % N;
    }
    printf("%d\n", ans);
  }
  return 0;
}
