#include <stdio.h>

int main(void)
{
  char line[1024];
  double dist = 0.0;
  double speed = 0.0;
  int last = 0;
  int curr;
  int h, m, s;
  int t;
  double v;

  while (fgets(line, 1024, stdin)) {
    t = sscanf(line, "%d:%d:%d %lf", &h, &m, &s, &v);
    curr = h*3600+m*60+s;
    dist += speed/3600.0 * (curr-last);
    if (t == 3) {
      printf("%02d:%02d:%02d %.2f km\n", h, m, s, dist);
    } else {
      speed = v;
    }
    last = curr;
  }

  return 0;
}
