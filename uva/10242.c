#include <stdio.h>

void swap(int *x, int *y, int i, int j)
{
  int t = x[i];
  x[i] = x[j];
  x[j] = t;
  t = y[i];
  y[i] = y[j];
  y[j] = t;
}

int main(void)
{
  int x[4], y[4];
  double xx, yy;
  int i;
  
  while (scanf("%lf %lf", &xx, &yy) == 2) {
    x[0] = (int)(xx*1000+0.5);
    y[0] = (int)(yy*1000+0.5);
    for (i = 1; i < 4; i++) {
      scanf("%lf %lf", &xx, &yy);
      x[i] = (int)(xx*1000+0.5);
      y[i] = (int)(yy*1000+0.5);
    }

    if (x[0] == x[3] && y[0] == y[3]) {
      swap(x, y, 2, 3);
    } else if (x[1] == x[2] && y[1] == y[2]) {
      swap(x, y, 0, 1);
    } else if (x[1] == x[3] && y[1] == y[3]) {
      swap(x, y, 0, 1);
      swap(x, y, 2, 3);
    }

    x[3] += x[1] - x[0];
    y[3] += y[1] - y[0];

    printf("%.3f %.3f\n", x[3]/1000.0, y[3]/1000.0);
  }
  
  return 0;

}
