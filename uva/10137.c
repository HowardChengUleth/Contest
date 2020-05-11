/* @JUDGE_ID: 1102NT 10137 C "" */

#include <stdio.h>

int main(void)
{
  int n, i;
  int t1, t2;
  int A[1000];
  int sum, rem, changed;

  while (scanf("%d", &n) == 1 && n > 0) {
    sum = changed = 0;
    for (i = 0; i < n; i++) {
      scanf("%d.%d", &t1, &t2);
      A[i] = t1*100+t2;
      sum += A[i];
    }
    rem = sum % n;
    sum /= n;
    for (i = 0; i < n; i++) {
      if (A[i] > sum) {
	changed += A[i] - sum;
	if (rem-- > 0) {
	  changed--;
	}
      }
    }
    printf("$%d.%02d\n", changed/100, changed%100);
  }
  return 0;
}
