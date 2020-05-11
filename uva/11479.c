#include <stdio.h>
#include <stdlib.h>

long long cmp(const void *a, const void *b)
{
  return *(long long *)a - *(long long *)b;
}


int main(void)
{
  int cases;
  int i;
  long long sides[3];

  scanf("%d", &cases);
  for (i = 1; i <= cases; i++) {
    scanf("%lld %lld %lld", sides, sides+1, sides+2);
    qsort(sides, 3, sizeof(*sides), cmp);
    printf("Case %d: ", i);
    if (sides[0] <= 0 || sides[0] + sides[1] <= sides[2]) {
      printf("Invalid\n");
    } else if (sides[0] == sides[2]) {
      printf("Equilateral\n");
    } else if (sides[0] == sides[1] || sides[1] == sides[2]) {
      printf("Isosceles\n");
    } else {
      printf("Scalene\n");
    }
  }
  return 0;
}
