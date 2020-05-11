/* @JUDGE_ID: 1102NT 10550 C "" */

#include <stdio.h>

int main(void)
{
  int start, d1, d2, d3;
  int angle;

  while (scanf("%d %d %d %d", &start, &d1, &d2, &d3) == 4 &&
	 (start || d1 || d2 || d3)) {
    angle = 360*2;
    angle += (start >= d1) ? (start-d1)*9 : (start+40-d1)*9;
    angle += 360;
    angle += (d1 < d2) ? (d2-d1)*9 : (d2+40-d1)*9;
    angle += (d2 > d3) ? (d2-d3)*9 : (d2+40-d3)*9;
    printf("%d\n", angle);
  }
  return 0;

}
