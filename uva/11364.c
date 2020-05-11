#include <stdio.h>

int main(void)
{
  int t, n;
  int min, max, x;

  scanf("%d", &t);
  while (t-- > 0) {
    scanf("%d", &n);
    
    scanf("%d", &min);
    max = min;
    n--;

    while (n-- > 0) {
      scanf("%d", &x);
      if (min > x) min = x;
      if (max < x) max = x;
    }
    
    printf("%d\n", 2*(max-min));
  }

  return 0;
}
