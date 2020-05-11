#include <stdio.h>
#include <math.h>

int calc_skew(double a, double b)
{
  int num[2];
  int count = 0;
  double height = 0.0;
  double inc = sqrt(3)/2.0;
  int i;

  num[0] = (int)floor(a);
  num[1] = (int)floor(a - 0.5);

  if (b >= 1.0) {
    count = num[0];
    height = 1.0;
  }

  i = 1;
  while (height + inc <= b) {
    height += inc;
    count += num[i];
    i = 1-i;
  }

  return count;
}

int main(void)
{
  double a, b;
  int grid, skew, skew1, skew2;

  while (scanf("%lf %lf", &a, &b) == 2) {
    grid = (int)(floor(a) * floor(b));
    skew1 = calc_skew(a, b);
    skew2 = calc_skew(b, a);
    skew = (skew1 > skew2) ? skew1 : skew2;
    if (grid < skew) {
      printf("%d skew\n", skew);
    } else {
      printf("%d grid\n", grid);
    }
  }

  return 0;
}
