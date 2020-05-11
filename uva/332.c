#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

long long gcd(long long a, long long b)
{
  if (!b) {
    return a;
  } else {
    return gcd(b, a%b);
  }
}

int main(void)
{
  int j, k;
  char exp[100];
  long long X;
  long long num, denom;
  long long g;
  int case_num = 1;

  while (scanf("%d 0.%s", &j, exp) == 2 && j != -1) {
    k = strlen(exp) - j;
    X = atoi(exp);    
    if (j == 0) {
      j++;
      X *= 10;
    }
    exp[k] = 0;
    num = floor(X - atoi(exp) + 0.5);
    denom = floor(pow(10, k+j) - pow(10, k) + 0.5);

    g = gcd(num, denom);
    num /= g;
    denom /= g;
    
    printf("Case %d: %lld/%lld\n", case_num++, num, denom);
  }
  return 0;
}
