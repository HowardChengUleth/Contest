#include <stdio.h>

double E(int n, double t, int prize)
{
  double temp, cutoff;

  if (n == 0) {
    return prize;
  }
  
  temp = E(n-1, t, 2*prize);
  cutoff = prize / temp;
  if (cutoff <= t) {
    /* always take another chance */
    return (temp/2 - t*t*temp/2) / (1-t);
  } else {
    /* need to integrate */
    
    return ((cutoff-t)*prize + temp/2 - cutoff*cutoff*temp/2) / (1-t);
  }
}

int main(void)
{
  int n;
  double t;

  while (scanf("%d %lf", &n, &t) == 2 && !(n == 0 && t == 0)) {
    printf("%.3f\n", E(n, t, 1));
  }
  return 0;
}
