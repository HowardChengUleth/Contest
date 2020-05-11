/* @JUDGE_ID: 1102NT 476 C "" */

#include <stdio.h>

typedef struct {
  double x1, x2, y1, y2;
} Rect;

Rect rect[10];
int n;

int inside(double x, double y, int i)
{
  return (rect[i].x1 < x && x < rect[i].x2 && 
	  rect[i].y1 < y && y < rect[i].y2);
}

int main(void)
{
  char s[2];
  int p_num = 1;
  double x, y;
  int i;
  int found;

  while (scanf("%s", s) == 1 && s[0] == 'r') {
    scanf("%lf %lf %lf %lf", &(rect[n].x1), &(rect[n].y2) , &(rect[n].x2),
	  &(rect[n].y1));
    n++;
  }

  while (scanf("%lf %lf", &x, &y) == 2 && !(x == 9999.9 && y == 9999.9)) {
    found = 0;
    for (i = 0; i < n; i++) {
      if (inside(x, y, i)) {
	printf("Point %d is contained in figure %d\n", p_num, i+1);
	found = 1;
      }
    }
    if (!found) {
      printf("Point %d is not contained in any figure\n", p_num);
    }
    p_num++;
  }
  return 0;
}
