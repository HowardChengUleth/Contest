#include <stdio.h>

int main(void)
{
  int cases;
  int m, n;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %d", &m, &n);
    printf("%d\n", (((m-2)+2)/3)*(((n-2)+2)/3));
  }
  return 0;
}
