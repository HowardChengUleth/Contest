#include <stdio.h>

long long solve(long long a, long long b)
{
  /* every intersection point is formed by two lines which are diagonals
     of a trapezoid, and vice versa.  Just count how many trapezoids
     we can form */
  long long ans;

  ans = (a % 2) ? (a-1)/2*a : a/2*(a-1);
  ans *= (b % 2) ? (b-1)/2*b : b/2*(b-1);

  return ans;
}

int main(void)
{
  int a, b;
  int case_num = 1;

  while (scanf("%d %d", &a, &b) == 2 && (a || b)) {
    printf("Case %d: %lld\n", case_num++, solve(a, b));
  }

  return 0;
}
