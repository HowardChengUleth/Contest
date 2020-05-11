#include <stdio.h>

int main(void)
{
  int T, G, L;

  scanf("%d", &T);
  while (T-- > 0) {
    scanf("%d %d", &G, &L);
    if (L % G) {
      printf("-1\n");
    } else {
      printf("%d %d\n", G, L);
    }
  }
  return 0;
}
