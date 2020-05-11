/* @JUDGE_ID: 1102NT 701 C "" */

#include <stdio.h>
#include <math.h>
#include <assert.h>

/*
 * Let p be the prefix, and we are looking for 2^k.
 *
 * Then if l is the length of the unknown part, we have
 *
 * p * 10^l + q = 2^k  with (q < 10^l)
 *
 * Taking log10 gives:
 *
 * log10(p) + l <= k * log10(2) < log10(p+1) + l
 *
 * log2(p) + l/log10(2) <= k < log2(p+1) + l/log10(2)
 *
 * so we want to look for l such that we obtain an integer k.
 *
 */

double log2(double x)
{
  return log10(x)/log10(2.0);
}

int main(void)
{
  unsigned int p;
  double a, b;
  double d, k1, k2;
  int l, digits;

  d = 1.0/log10(2.0);
  while (scanf("%ud", &p) == 1) {
    a = log2((double)p);
    b = log2((double)p+1.0);
    digits = floor(log10((double)p))+1;
    for (l = digits+1; ; l++) {
      k1 = ceil(a + l*d);
      k2 = floor(b + l*d);
      if (fabs(k1-k2) < 0.1) {
        printf("%d\n", (int)floor(k1+0.3));
        break;
      }
    }
  }
  
  return 0;
}
