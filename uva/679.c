#include <stdio.h>

void solve(int D, int I)
{
  int start, num;   /* [start, start+num) is the list of potential leaves */
  int i;

  start = num = 1;
  for (i = 0; i < D-1; i++) {
    start *= 2;
    num *= 2;
  }
  
  while (num > 1) {
    if (I % 2 == 0) {
      /* right half */
      start += num/2;
    }      /* nothing to do with left half */
    num /= 2;
    I = (I+1)/2;
  }

  printf("%d\n", start);
}

int main(void)
{
  int D, I;
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %d", &D, &I);
    solve(D, I);
  }

  return 0;
}
