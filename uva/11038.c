#include <stdio.h>
#include <string.h>

/* number of 0's from 10^k to 10^(k+1)-1
 *
 * This can be computed as follows: if there are k+1 digits, then the first
 * must be nonzero but the remaining can have any number of zeros.  For
 * each possible number of zeros appearing (at most k), we look at all
 * possible ways to distibute these zeros and then all possible ways to
 * choose the nonzero digits.  This gives:
 *
 * sum(9^i * i * binomial(k, i), i=1..k)
 *
 * which simplifies (use Maple) to:
 *
 * 9*k*10^(k-1)
 *
 */

long long f[12];

/* number of 0's from 0 to 10^(k+1)-1 */
long long g[12];

void comp_fg(void)
{
  int i, j;

  for (i = 0; i < 11; i++) {
    f[i] = 9 * i;
    for (j = 0; j < i-1; j++) {
      f[i] *= 10;
    }
  }

  g[0] = 1;
  for (i = 1; i < 11; i++) {
    g[i] = f[i] + g[i-1];
  }

}

/* number of 0's from 0 to n */
long long zeros(long long n)
{
  char s[1024];
  int k, i, j;
  long long ans = 0;
  long long m, t;

  sprintf(s, "%lld", n);
  k = strlen(s);

  /* just one digit, easy */
  if (k == 1) {
    return 1;
  }

  /* first get 0 to 10^(k-1)-1 */
  ans += g[k-2];

  /* now get j * 10^(k-1) to j * 10^(k-1) + 10^(k-2)-1 
     for j = 1, 2, ..., s[0]-1 */
  t = 1;
  for (j = 0; j < k-1; j++) {
    t *= 10;
  }
  
  ans += (s[0]-'0'-1) * ((t-10)/9 + g[k-2]);
     
  /* now recurse */
  sscanf(s+1, "%lld", &m);
  
  /* take care of leading 0's before recursing */
  for (i = 1; i < k-1 && s[i] == '0'; i++) {
    ans += m+1;
  }

  if (s[i] != '0') {
    if (i < k-1) {
      t = 1;
      for (j = 0; j < k-i; j++) {
	t *= 10;
      }
      ans += (t - 10) / 9;
    }
  }
  return ans + zeros(m);
}

int main(void)
{
  long long m, n;

  comp_fg();
  while (scanf("%lld %lld", &m, &n) == 2 && m >= 0) {
    printf("%lld\n", (m == 0) ? zeros(n) : zeros(n) - zeros(m-1));
  }
  return 0;
}
