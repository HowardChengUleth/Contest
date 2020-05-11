/* @JUDGE_ID: 1102NT 10555 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

long long gcd(long long a, long long b)
{
  long long r;

  /* unnecessary if a, b >= 0 */
  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  assert(a >= 0);
  return a;
}

int main(void)
{
  char line[10000], temp[10000];
  int len, k, i;
  long long a, b, a2, b2, ta, tb, tc, td, g;

  while (fgets(line, 10000, stdin) && strcmp(line, "0\n")) {
    len = strlen(line)-1-3;
    line[len] = 0;
    
    b = 0;

    for (k = len-2; k >= 1; k--) {
      strcpy(temp, line);
      temp[len-k] = 0;
      ta = atoi(temp+2);
      tb = 10;
      for (i = 1; i < len-k-2; i++) {
	tb *= 10;
      }
      g = gcd(ta, tb);
      ta /= g; tb /= g;


      tc = atoi(line+len-k);
      td = 9;
      for (i = 1; i < k; i++) {
	td = td*10 + 9;
      }
      for (i = 0; i < len-k-2; i++) {
	td *= 10;
      }
      g = gcd(tc,td);
      tc /= g; td /= g;
      
      a2 = ta*td  + tb*tc;
      b2 = tb*td;
      g = gcd(a2,b2);
      a2 /= g; b2 /= g;

      if (b == 0 || b2 < b) {
	a = a2;
	b = b2;
      }
    }
    printf("%lld/%lld\n", a, b);
  }
  return 0;
}
