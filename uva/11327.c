/*
 * The idea is this:
 *
 * The number of fractions with a certain denominator d is phi(d) if d > 1.
 * For d = 1, the number is 2 (0/1, 1/1).
 *
 * So if we keep a list of the number of fractions with denominator up to
 * and including d (sum of phi(i) from 2 to d, plus 2), we can use binary
 * search on this list to quickly locate the denominator.
 *
 * Once we have the denominator, we can quickly find out what position it
 * is in within all fractions having the same denominator, and then
 * search through all numbers until we find enough numerators that are
 * relatively prime to d.
 *
 */

#include <stdio.h>
#include <assert.h>

int fast_exp(int b, int n)
{
  int res = 1;
  int x = b;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res *= x;
    } else {
      n >>= 1;
      x *= x;
    }
  }

  return res;
}

int phi(int n) {
  int k, res;
  long long p;

  assert(n > 0);

  res=1;
  for(k = 0; n % 2 == 0; k++) {
    n /= 2;
  }
  if (k)
    res *= fast_exp(2, k-1);

  for (p = 3; p*p <= n; p += 2) {
    for (k = 0; n % p == 0; k++) {
      n /= p;
    }
    if (k) {
      res *= fast_exp(p, k-1) * (p-1);
    }
  }
  if (n > 1) {
    res *= n-1;
  }
  return res;
}

int bin_search(long long *A, int n, long long x, int *index)
{
   int l, u, m;

   if (n <= 0 || x < A[0]) {
      *index = 0;
      return 0;
   }
   if (A[n-1] < x) {
      *index = n;
      return 0;
   }
   if (x == A[n-1]) {
      *index = n-1;
      return 1;
   }
   l = 0;
   u = n-1;
   while (l+1 < u) {
      assert(A[l] <= x && x < A[u]);
      m = (l+u)/2;
      if (A[m] <= x) {
         l = m;
      } else {
         u = m;
      }
   }
   if (A[l] == x) {
      *index = l;
      return 1;
   } else {
      *index = u;
      return 0;
   }
}

int gcd(int a, int b)
{
  int r;

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int main(void)
{
  long long total[200001];    /* total number of rational numbers with 
				 denominator at most the index */
  char isprime[200001];
  int i;
  int d, n, inc, t;
  long long k, c;
  
  total[0] = 0;
  total[1] = 2;
  for (i = 2; i <= 200000; i++) {
    t = phi(i);
    total[i] = total[i-1] + t;
    isprime[i] = (t == i-1);
  }

  while (scanf("%lld", &k) == 1 && k) {
    if (bin_search(total+1, 200000, k, &d)) {
      printf("%d/%d\n", (d ? d : 1), d+1);
    } else {
      d++;
      c = k - total[d-1];
      if (isprime[d]) {
	printf("%lld/%d\n", c, d);
	continue;
      }
      n = (d & 1) ? 0 : 1;
      inc = (d & 1) ? 1 : 2;
      while (1) {
	if (gcd(n, d) == 1) {
	  if (--c == 0) {
	    printf("%d/%d\n", n, d);
	    break;
	  }
	}
	n += inc;
      }
    }
  }

  return 0;
}









