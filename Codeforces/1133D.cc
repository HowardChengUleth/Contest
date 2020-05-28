#include <bits/stdc++.h>

using namespace std;

// in order for c_i = d * a_i + b_i = 0, we must have
//
//    d = -b_i / a_i
//
// So basically we are just looking for the ratio -b_i/a_i that occurs
// the most often.  The only "trick" is that we do not want to convert
// this to floating point numbers, so we will actually just represent
// this as a "fraction".  The "fraction" below actually works even
// when the denominator is 0, but in that case it only works if b_i = 0.
// And since d can be anything, we will just solve the problem without this
// case and add the number of (0,0) pairs to the answer

typedef long long ll;

ll gcd(ll a, ll b)
{
  if (a < 0) {
    return gcd(-a, b);
  }
  if (b < 0) {
    return gcd(a, -b);
  }
  if (!b) return a;
  return gcd(b, a%b);
}

struct Fraction
{
  ll num, den;

  Fraction(int n, int d)
    : num{n}, den{d}
  {
    if (den < 0) {
      num *= -1;
      den *= -1;
    }
    ll g = gcd(num, den);
    if (g) {
      num /= g;
      den /= g;
    }
  }

  bool operator<(const Fraction &f) const
  {
    return f.den*num < den*f.num;
  }
  
  bool operator==(const Fraction &f) const
  {
    return num == f.num && den == f.den;
  }
};

int main()
{
  int n;
  cin >> n;

  int a[200000], b[200000];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  int zerooverzero = 0;
  map<Fraction, int> freq;
  for (int i = 0; i < n; i++) {
    if (a[i] != 0) {
      freq[Fraction(-b[i], a[i])]++;
    } else if (b[i] == 0) {
      zerooverzero++;
    }
  }

  int ans = 0;
  for (auto p : freq) {
    ans = max(ans, p.second);
  }

  cout << ans + zerooverzero << endl;

  
  return 0;
}
