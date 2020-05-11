#include <stdio.h>
#include <math.h>

int main(void)
{
  double Vtotal, V0;
  int n;
  int best_n;
  double best, temp;

  while (scanf("%lf %lf", &Vtotal, &V0) == 2 && (Vtotal != 0.0 || V0 != 0.0)) {
    n = 1;
    best = -1;
    best_n = 0;
    while (Vtotal / n > V0) {
      temp = (Vtotal - V0*n) *n;
      if (temp > best) {
	best = temp;
	best_n = n;
      } else if (fabs(temp-best) < 1e-8) {
	best_n = 0;
      }
      n++;
    }
    printf("%d\n", best_n);

  }
  return 0;
}
