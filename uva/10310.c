#include <stdio.h>
#include <math.h>

typedef struct {
  long long x, y;
} Point;


int main(void)
{
  int n;
  Point gopher, dog, hole;
  long long dist_g, dist_d;
  int i, esc;
  double x, y;

  while (scanf("%d", &n) == 1) {
    scanf("%lf %lf", &x, &y);
    gopher.x = (long long)floor(x*1000+0.5);
    gopher.y = (long long)floor(y*1000+0.5);
    scanf("%lf %lf", &x, &y);
    dog.x = (long long)floor(x*1000+0.5);
    dog.y = (long long)floor(y*1000+0.5);
    esc = 0;
    for (i = 0; i < n; i++) {
      scanf("%lf %lf", &x, &y);
      hole.x = (long long)floor(x*1000+0.5);
      hole.y = (long long)floor(y*1000+0.5);

      if (!esc) {
	dist_g = (hole.x-gopher.x)*(hole.x-gopher.x) + 
	  (hole.y-gopher.y)*(hole.y-gopher.y);
	dist_d = (hole.x-dog.x)*(hole.x-dog.x) + (hole.y-dog.y)*(hole.y-dog.y);
	if (dist_g*4 <= dist_d) {
	  printf("The gopher can escape through the hole at (%.3f,%.3f).\n",
		 hole.x/1000.0, hole.y/1000.0);
	  esc = 1;
	}
      }
    }
    if (!esc) {
      printf("The gopher cannot escape.\n");
    }
  }
  return 0;
}
