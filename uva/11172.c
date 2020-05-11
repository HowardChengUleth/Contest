#include <stdio.h>

int main(void)
{
  int n;
  int a, b;

  scanf("%d", &n);
  while (n-- > 0) {
    scanf("%d %d", &a, &b);
    if (a < b) {
      printf("<\n");
    } else if (a > b) {
      printf(">\n");
    } else {
      printf("=\n");
    }
  }
  return 0;

}
