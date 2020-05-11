/* @JUDGE_ID: 1102NT 10056 C "" */

#include <stdio.h>
#include <math.h>

int main(void)
{
  int cases;
  int n, l;
  double p, ans, t;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %lf %d", &n, &p, &l);
    ans = 0.0;
    t = pow(1-p, l-1)*p;
    while (t > 1e-6) {
      ans += t;
      t *= pow(1-p, n);
    }
    printf("%.4f\n", ans);
  }
  return 0;
}
