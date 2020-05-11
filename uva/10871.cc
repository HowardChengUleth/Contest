#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

const int MAX_SIEVE = 10000000;
const int MAX_PRIMES = 1000000;
bool prime[MAX_SIEVE+1];
int primes[MAX_PRIMES];
int num_primes;

bool isprime(int n)
{
  if (n <= MAX_SIEVE) {
    return prime[n];
  }

  for (int i = 0; i < num_primes; i++) {
    int p = primes[i];
    if (p*p > n) break;
    if (n % p == 0) return true;
  }
  return true;
}

int main(void)
{
  prime[0] = prime[1] = false;
  fill(prime+2, prime+MAX_SIEVE+1, true);
  for (int p = 2; p <= MAX_SIEVE; p++) {
    if (!prime[p]) continue;
    primes[num_primes++] = p;
    for (int i = p+p; i <= MAX_SIEVE; i += p) {
      prime[i] = false;
    }
  }
  
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int A[10000], p[10001];
    int n;
    cin >> n;
    for (int j = 0; j < n; j++) {
      cin >> A[j];
    }
    p[0] = 0;
    partial_sum(A, A+n, p+1);

    bool found = false;
    for (int len = 2; len <= n && !found; len++) {
      for (int start = 0; start + len - 1 < n; start++) {
	if (isprime(p[start+len] - p[start])) {
	  found = true;

	  cout << "Shortest primed subsequence is length " << len << ":";
	  for (int j = start; j < start+len; j++) {
	    cout << ' ' << A[j];
	  }
	  cout << endl;
	  break;
	}
      }
    }
    if (!found) {
      cout << "The sequence is anti-primed." << endl;
    }
  }

  return 0;
}
