/* @JUDGE_ID: 1102NT 10692 C "" */

#include <stdio.h>

#include <stdlib.h>
#include <assert.h>
 
int gcd(int a, int b, int *s, int *t)
{
  int r, r1, r2, a1, a2, b1, b2, q;
  int A = a;
  int B = b;
 
  a1 = b2 = 1;
  a2 = b1 = 0;
 
  while (b) {
    assert(a1*A + a2*B == a);
    q = a / b;
    r = a % b;
    r1 = a1 - q*b1;
    r2 = a2 - q*b2;
    a = b;
    a1 = b1;
    a2 = b2;
    b = r;
    b1 = r1;
    b2 = r2;
  }
 
  *s = a1;
  *t = a2;
  assert(a >= 0);
  return a;
}

int cra(int n, int *m, int *a)
{
  int x, i, k, prod, temp;
  int gamma[2], v[2];

  /* compute inverses */
  for (k = 1; k < n; k++) {
    prod = m[0] % m[k];
    for (i = 1; i < k; i++) {
      prod = (prod * m[i]) % m[k];
    }
    gcd(prod, m[k], gamma+k, &temp);
    gamma[k] %= m[k];
    if (gamma[k] < 0) {
      gamma[k] += m[k];
    }
  }

  /* compute coefficients */
  v[0] = a[0];
  for (k = 1; k < n; k++) {
    temp = v[k-1];
    for (i = k-2; i >= 0; i--) {
      temp = (temp * m[i] + v[i]) % m[k];
      if (temp < 0) {
        temp += m[k];
      }
    }
    v[k] = ((a[k] - temp) * gamma[k]) % m[k];
    if (v[k] < 0) {
      v[k] += m[k];
    }
  }

  /* convert from mixed-radix representation */
  x = v[n-1];
  for (k = n-2; k >= 0; k--) {
    x = x * m[k] + v[k];
  }

  return x;
}


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

int fast_exp_mod(int b, int n, int m)
{
  int res = 1;
  int x = b % m;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res *= x;
      res %= m;
    } else {
      n >>= 1;
      x *= x;
      x %= m;
    }
  }

  return res;
}

int factor(int n, int *factors)
{
  int count = 0;
  int p;

  while (n % 2 == 0) {
    n /= 2;
    factors[count++] = 2;
  }
  
  for (p = 3; p*p <= n; p += 2) {
    while (n % p == 0) {
      n /= p;
      factors[count++] = p;
    }
  }
  if (n > 1) {
    factors[count++] = n;
  }
  return count;
}

int phi(int n)
{
  int factors[32];
  int count;
  int val = 1;
  int i, j;

  count = factor(n, factors);
  for (i = 0; i < count; i = j) {
    for (j = i; j < count && factors[j] == factors[i]; j++)
      ;
    val *= fast_exp(factors[i], j-i-1) * (factors[i]-1);
  }
  return val;
}

int phi_vals[10001];

int is_zero(int n, int *a)
{
  if (a[0] != 0) {
    return 0;
  } else {
    return n == 1 || !is_zero(n-1, a+1);
  }
}

/* check if a[0]^...^a[n-1] >= N */
int exp_geq(int n, int *a, int N)
{
  int k, b;

  if (n == 1) {
    return a[0] >= N;
  }
  if (a[0] == 1) {
    /* then a[0]^...^a[n-1] == 1 */
    return 1 >= N;
  }
  if (a[0] == 0) {
    /* then the answer is either 0 or 1 */
    if (is_zero(n-1, a+1)) {
      return 1 >= N;
    } else {
      return 0 >= N;
    }
  }
  if (N <= 1) {
    /* we have already taken care of a[0] == 0 */
    return 1;
  }

  b = a[0];
  for (k = 0; b < N; k++) {
    b *= a[0];
  }
  return exp_geq(n-1, a+1, k+1);
}

int find_exp(int n, int *a, int m)
{
  int factors[32], count;
  int power, i, mod[2], x[2];

  /* base case: if there is only one exponent, easy */
  if (n == 1) {
    return a[0] % m;
  }

  /* special case: if exponent is 0, just return 1 */
  if (is_zero(n-1, a+1)) {
    return 1;
  }

  /* special case: if a[0] = 0 */
  if (a[0] % m == 0) {
    return 0;         /* we know that we cannot have 0^0 */
  }

  /* special case: if m == 2 */
  if (m == 2) {
    return 1;  /* we know we cannot have 0^0 or a[0] % 2 == 0 */
  }

  count = factor(m, factors);

  if (count == 1) {
    /* m is prime, easy case */
    power = find_exp(n-1, a+1, phi_vals[m]);
    return fast_exp_mod(a[0], power, m);
  } else if (factors[0] == factors[count-1]) {
    /* prime power case */
    if (a[0] % factors[0]) {
      /* not zero divisor, just do the easy thing */
      power = find_exp(n-1, a+1, phi_vals[m]);
      return fast_exp_mod(a[0], power, m);
    } else {
      if (exp_geq(n-1, a+1, count)) {
	/* exponent is larger than count, so it can only be 0 */
	return 0;
      } else {
	/* exponent is small, so just do it.  Note that it can still be
	   0, because factors[0] may divide into a[0] more than once. */
	power = a[n-1];
	for (i = n-2; i > 0; i--) {
	  power = fast_exp(a[i], power);
	}
	return fast_exp_mod(a[0], power, m);
      }
    }
  } else {
    /* mixed primes, do Chinese remaindering */
    mod[0] = 1;
    for (i = 0; i < count && factors[i] == factors[0]; i++) {
      mod[0] *= factors[i];
    }
    mod[1] = m / mod[0];
    x[0] = find_exp(n, a, mod[0]);
    x[1] = find_exp(n, a, mod[1]);
    return cra(2, mod, x);
  }
}

int main(void)
{
  int i, m, n, a[10], case_no = 1;
  
  for (i = 2; i <= 10000; i++) {
    phi_vals[i] = phi(i);
  }

  while (scanf("%d", &m) == 1) {
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
      scanf("%d", a+i);
    }
    printf("Case #%d: %d\n", case_no++, find_exp(n, a, m));
  }

  return 0;
}
