/* @JUDGE_ID: 1102NT 846 C "" */

#include <stdio.h>
#include <math.h>

int main(void)
{
  int cases;
  int x, y, d;
  int k, steps;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %d", &x, &y);
    d = y - x;
    if (d == 0) {
      steps = 0;
    } else {
      steps = 2*floor(sqrt(d))-1;
      k = steps/2;
      
      while (((steps % 2) ? (k+1)*(k+1) : k*(k+1)) < d) {
	steps++;
	k = steps/2;
      }
    }
    printf("%d\n", steps);
  }
  return 0;
}
