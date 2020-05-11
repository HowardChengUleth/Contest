#include <stdio.h>
#include <limits.h>

int main(void)
{
  int cases;
  int n, prev, next;
  int count, up;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d", &n);
    up = 1;
    count = 0;
    prev = INT_MIN;
    while (n-- > 0) {
      scanf("%d", &next);
      if (up == 1 && next < prev) {
	count++;
	up = 0;
      } else if (up == 0 && next > prev) {
	count++;
	up = 1;
      }
      prev = next;
    }
    count++;
    printf("%d\n", count);
  }
  return 0;
}
