#include <stdio.h>

int main(void)
{
  int cases, n, m;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %d", &n, &m);
    if ((n-1) % (m-1)) {
      printf("cannot do this\n");
    } else {
      printf("%d\n", (n-1)/(m-1));
    }
  }
  return 0;
}
