#include <bits/stdc++.h>

using namespace std;

// to compute pi(n), use a sieve.  It grows roughly n/log n.
//
// for rub(n), it is roughly 10^(length(n)/2).  e.g. if we want to look at
// the number of 10 digit palindrome, then you can do anything you want for
// the first 5 digits (except leading 0) and the last 5 digits are determined.
// This is about sqrt(n)
//
// So pi(n) definitely grows faster than rub(n).
//
// look at n/log n vs 42*sqrt(n), it will not take long for pi(n) > A*rub(n)
// certainly no more than 2000000

typedef long long ll;

const int MAX = 2000000;
int pi[MAX+1], rub[MAX+1];

int reverse(int n)
{
  int ans = 0;
  while (n > 0) {
    ans = ans * 10 + n % 10;
    n /= 10;
  }
  return ans;
}

int main()
{
  // compute pi
  bool sieve[MAX+1] = {0};
  fill(sieve+2, sieve+MAX+1, true);
  for (ll p = 2; p <= MAX; p++) {
    pi[p] = pi[p-1];
    if (!sieve[p]) continue;
    pi[p]++;
    for (ll j = p*p; j <= MAX; j += p) {
      sieve[j] = false;
    }
  }

  // compute rub
  bool palin[MAX+1] = {0};
  for (int i = 1; i <= MAX; i++) {
    palin[i] = (i == reverse(i));
    rub[i] = rub[i-1] + palin[i];
  }

  int p, q;
  cin >> p >> q;
  for (int i = MAX; i >= 1; i--) {
    if (q*pi[i] <= p*rub[i]) {
      cout << i << endl;
      return 0;
    }
  }

  cout << "Palindromic tree is better than splay tree" << endl;
  return 0;
}
