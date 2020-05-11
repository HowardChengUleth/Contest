#include <stdio.h>

int main(void)
{
  int v, t;

  while (scanf("%d %d", &v, &t) == 2) {
    printf("%d\n", v*t*2);
  }
  return 0;
}
