#include <stdio.h>
#include <math.h>
#include <assert.h>

#define MAX_N 1000

double d[MAX_N], a[MAX_N];
int n;
double pi;

int read_case(void)
{
  int i, deg, min, sec;

  scanf("%d", &n);
  if (!n) {
    return 0;
  }

  for (i = 0; i < n; i++) {
    if (i) {
      scanf("%lf %dd%d'%d\"", d+i, &deg, &min, &sec);
      a[i] = (deg + min/60.0 + sec/3600.0) * pi / 180.0;
    } else {
      scanf("%lf %d", d+i, &deg);
      assert(!deg);
    }
  }

  return 1;
}

int acceptable(void)
{
  double x, y, total, dist;
  double angle;  /* angle clockwise from neg x-axis */
  int i;

  x = d[0];  y = 0.0;
  total = d[0];
  angle = pi;
  /*  printf("0, x, y = (%7.4f,%7.4f)\n", x, y); */
  
  for (i = 1; i < n; i++) {
    angle += a[i] - pi;
    x += d[i]*cos(pi-angle);
    y += d[i]*sin(pi-angle);
    total += d[i];
    /*    printf("%d: x, y = (%7.4f,%7.4f)\n", i, x, y); */
  }
  
  dist = sqrt(x*x + y*y);
  return (dist/total < 0.001);
}

int main(void)
{
  pi = acos(-1);
  while (read_case()) {
    if (acceptable()) {
      printf("Acceptable\n");
    } else {
      printf("Not acceptable\n");
    }
  }
  return 0;
}
