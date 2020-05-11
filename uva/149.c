/* @JUDGE_ID: 1102NT 149 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define EPSILON 1E-8
#define NDEBUG

static double d, x, y;
static char ang_used[360000];
static int ang_left;
static double pi;
static int extend;

double dist(double x1, double y1, double x2, double y2)
{
  double dx = x1-x2;
  double dy = y1-y2;

  return sqrt(dx*dx+dy*dy);
}

int fill(int start, int end)
{
  int flag = 1;
  int i, j, k, c;

  i = start - 1;
  do {
    if (++i >= 360000) {
      i = 0;
    }
    if (ang_used[i]) {
      flag = 0;
    } else {
      ang_used[i] = 1;
      ang_left--;
    }
  } while (i != end);

  if (extend) {
    c = 0;
    j = k = (end == 359999) ? 0 : end+1;
    while (!ang_used[j] && c <= 9) {
      c++;
      if (++j >= 360000) {
	j = 0;
      }
    }
    if (c <= 9) {
      while (k != j) {
	assert(!ang_used[k]);
	ang_used[k] = 1;
	ang_left--;
	if (++k >= 360000) {
	    k = 0;
	}
      }
    }
    c = 0;
    j = k = (start == 0) ? 359999 : start-1;
    while (!ang_used[j] && c <= 9) {
      c++;
      if (--j < 0) {
	j = 359999;
      }
    }
    if (c <= 9) {
      while (k != j) {
	assert(!ang_used[k]);
	ang_used[k] = 1;
	ang_left--;
	if (--k < 0) {
	    k = 359999;
	}
      }
    }
  }

  return flag;
}

int process(double t_x, double t_y, double *width)
{
  double ang;
  int start, end;

  assert(dist(x, y, t_x, t_y) > EPSILON);
  *width = atan((d/2)/dist(x, y, t_x, t_y));
  if (*width < 0) {
    *width += 2*pi;
  }
  *width *= (180.0/pi);
  
  ang = atan2(t_y-y, t_x-x);
  if (ang < 0) {
    ang += 2*pi;
  }
  ang *= (180.0/pi);

  start = floor((ang - *width) * 1000 + 0.5) - 10;
  end = floor((ang + *width) * 1000 + 0.5) + 10;
  if (start < 0) {
    start += 360000;
  }
  if (end >= 360000) {
    end -= 360000;
  }

  assert(0 <= start && start < 360000);
  assert(0 <= end && end < 360000);

  *width = floor(*width * 2.0 * 100 + 0.5) / 100.0;

  return fill(start, end);
}

int solve(void)
{
  int count = 0, old_count, same = 0;
  int i, r;
  double width, t_width;

  memset(ang_used, 0, 360000);

  width = 100;
  r = 0;
  extend = 0;
  ang_left = 360000;

  while (ang_left > 0 && width > 0.01 && same < 15) {
    old_count = count;
    if (r > 10) {
      extend = 1;
    }
    if (r == 0) {
      if (process(0, 0, &width)) {
	count++;
      }
    }
    width = 0;
    for (i = -r; i <= r; i++) {
      if (process(r, i, &t_width)) {
	count++;
      }
      if (t_width > width) {
	width = t_width;
      }
      if (process(-r, i, &t_width)) {
	count++;
      }
      if (t_width > width) {
	width = t_width;
      }
    }
    for (i = -r+1; i <= r-1; i++) {
      if (process(i, r, &t_width)) {
	count++;
      }
      if (t_width > width) {
	width = t_width;
      }
      if (process(i, -r, &t_width)) {
	count++;
      }
      if (t_width > width) {
	width = t_width;
      }
    }
    /*
    fprintf(stderr, "r = %d, count = %d\n", r, count);
    */

    if (count == old_count) {
      same++;
    }
    r++;
  }

  return count;
}

int main(void)
{
  pi = 4*atan(1);
  while (scanf("%lf %lf %lf", &d, &x, &y) == 3 &&
	 (d != 0 || x != 0 || y != 0)) {
    printf("%d\n", solve());
  }

  return 0;
}
