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

int eulerphi[200001];

void compute_phi(void)
{
  int n, p;
  long long t;
  int factors[200001];
  int prime[200001];

  for (n = 1; n <= 200000; n++) {
    eulerphi[n] = 1;
    prime[n] = 1;
  }

  for (p = 2; p <= 200000; p++) {
    if (!prime[p]) continue;
    for (n = 2*p; n <= 200000; n += p) {
      prime[n] = 0;
      factors[n] = 0;
    }

    for (t = p; t <= 200000; t *= p) {
      for (n = t; n <= 200000; n += t) {
	factors[n]++;
      }
    }
    
    for (n = p; n <= 200000; n += p) {
      eulerphi[n] *= fast_exp(p, factors[n]-1) * (p-1);
    }
  }

}


int main(void)
{
  long long G[200001];
  int N, k, n;

  /* G(N) = \sum_{i=1}^{N-1} \sum_{j=i+1}^N \gcd(i,j)
          = \sum_{i=1}^{N-2} \sum_{j=i+1}^N \gcd(i,j) + gcd(N-1,N)
          = \sum_{i=1}^{N-2} \sum_{j=i+1}^N \gcd(i,j) + gcd(N-1,N)
          = \sum_{i=1}^{N-2} (\sum_{j=i+1}^{N-1} \gcd(i,j) + gcd(i,N)) + 
	    gcd(N-1,N)
          = G(N-1) + \sum_{i=1}^{N-1} gcd(i, N)

     Now, \sum_{i=1}^{N-1} gcd(i, N) = gcd(1,N) + gcd(2,N) + ... + gcd(N-1,N).
     
     The number of gcd(i,N) = 1 is phi(N)
     The number of gcd(i,N) = 2 is phi(N/2) if N is even, otherwise 0
     etc.

     so we want to add phi(N) + 2*phi(N/2) + 3*phi(N/3) + ... + 
                       (N-1)*phi(N/(N-1)).

     but only include the terms that where N/k is an integer.  So we
     can use a sieve.
  */

  compute_phi();
  for (N = 2; N <= 200000; N++) {
    G[N] = 0;
  }

  for (k = 1; k <= 200000; k++) {
    for (n = 2*k; n <= 200000; n += k) {
      G[n] += k*eulerphi[n/k];
    }
  }
  for (N = 2; N <= 200000; N++) {
    G[N] += G[N-1];
  }

  while (scanf("%d", &N) == 1 && N > 0) {
    printf("%lld\n", G[N]);
  }

  return 0;
}
