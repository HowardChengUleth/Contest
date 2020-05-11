/* @JUDGE_ID: 1102NT 138 C "" */

#include <stdio.h>
#include <math.h>

int main(void)
{
  long long n, m, n2, count, temp;

  count = 0;
  m = 2;
  temp = (m*m+m)/2;
  n = n2 = 1;
  while (count < 10) {
    while (n2 < temp) {
      n2 += (n << 1) + 1;
      n++;
    }
    if (n < m && n2 == temp) {
      count++;
      printf("%10lld%10lld\n", n, m);
    }
    temp += m+1;
    m++;
  }
  return 0;
}
