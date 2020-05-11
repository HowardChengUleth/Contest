/* @JUDGE_ID: 1102NT 10170 C "" */

#include <stdio.h>
#include <math.h>

int main(void)
{
  long long S, D;
  long long A, B, C;

  /* We want the smallest n such that

     n*(n+1)/2 - S*(S-1)/2 >= D

     so we solve the quadratic, look for the positive root, and round
     up
  */

  while (scanf("%lld %lld", &S, &D) == 2) {
    A = B = 1;
    C = -(2*D + S*(S-1));
    printf("%.0f\n", ceil((-B + sqrt(B*B - 4*A*C))/2.0));
  }
  return 0;
}
