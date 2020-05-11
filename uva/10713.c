/* @JUDGE_ID: 1102NT 10713 C "" */

#include <stdio.h>
#include <math.h>

#define EPS 1e-12

double min(double x, double y)
{
  return (x < y) ? x : y;
}

int sign(double x)
{
  if (x > EPS) {
    return 1;
  } else if (x < -EPS) {
    return -1;
  } else {
    return 0;
  }
}

void move(double x, double y, double X, double Y)
{
  double dx = X - x;
  double dy = Y - y;

  if (fabs(dx) < EPS && fabs(dy) < EPS)
    return;
  
  if (fabs(dy) > EPS) {
    if (dy > 0) {
      printf("north");
    } else {
      printf("south");
    }
  }
  if (fabs(dx) > EPS) {
    if (dx > 0) {
      printf("east");
    } else {
      printf("west");
    }
  }

  printf(" %.10f\n", sqrt(dx*dx+dy*dy));
}

int main(void)
{
  double r, x, y, X, Y, x2, y2;
  double dx, dy, t;
  int first = 1;

  while (scanf("%lf", &r) == 1 && fabs(r+1) > 1e-10) {
    if (!first) {
      printf("\n");
    }
    first = 0;
    scanf("%lf %lf %lf %lf", &x, &y, &X, &Y);
    dx = X - x;
    dy = Y - y;

    if (fabs(dx) < EPS || fabs(dy) < EPS) {
      move(x, y, X, Y);
    } else {
      t = min(fabs(dx), fabs(dy));
      x2 = x + sign(dx)*t;
      y2 = y + sign(dy)*t;
      if (x2*x2+y2*y2 > r*r) {
	x2 = X - sign(dx)*t;
	y2 = Y - sign(dy)*t;
      }
      move(x, y, x2, y2);
      move(x2, y2, X, Y);
    }

  }
  return 0;
}
