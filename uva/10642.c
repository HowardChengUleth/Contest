#include <stdio.h>

int solve(int x1, int y1, int x2, int y2)
{
  int diag1 = x1+y1, diag2 = x2+y2;
  int sum = 0;

  if (diag1 == diag2) {
    return x2 - x1;
  }

  /* move to the beginning of next diagonal */
  sum = diag1+1 - x1;
  
  /* move to the beginning of diag2 */
  diag1++;
  while (diag1 < diag2) {
    sum += diag1 + 1;
    diag1++;
  }
  
  /* move along diag2 */
  sum += x2;
  
  return sum;
}

int main(void)
{
  int n;
  int i;
  int x1, y1, x2, y2;

  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    printf("Case %d: ", i);
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    printf("%d\n", solve(x1, y1, x2, y2));
  }
  return 0;
}
