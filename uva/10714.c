/* @JUDGE_ID: 1102NT 10714 C "" */

#include <stdio.h>

int main(void)
{
  int l, n;
  int dist;
  int cases;
  int earliest, latest;
  int t1, t2;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %d", &l, &n);
    earliest = latest = -1;
    while (n-- > 0) {
      scanf("%d", &dist);
      t1 = dist;
      t2 = l-dist;
      if (t1 > t2) {
	t1 = l-dist;
	t2 = dist;
      }
      if (t1 > earliest) {
	earliest = t1;
      }
      if (t2 > latest) {
	latest = t2;
      }
    }
    printf("%d %d\n", earliest, latest);
  }
  
  return 0;
}
