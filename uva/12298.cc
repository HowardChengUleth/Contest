// idea:
//
// we represent each suit as the generating function
//
//    f(i,x) =  sum x^k
//               k 
//
// where i is the index of the suit, and k is a card for that suit that is not missing (only composite k).
//
// Then f(0,x)*f(1,x)*f(2,x)*f(3,x) is the generating function for choosing one card from each suit.
// So we multiply them together and read off the coefficients.
//
// We use Karatsuba multiplication which has complexity O(n^1.585).

#include <iostream>
#include <algorithm>

using namespace std;

bool prime[50001];
int fmax[50001];
int suiti[256];

typedef long long ll;

void printpoly(ll p[], int deg)
{
  cout << "(";
  bool printed = false;
  for (int i = 0; i <= deg; i++) {
    if (p[i]) {
      if (printed) cout << " + ";
      cout << p[i] << "*x^" << i;
      printed = true;
    }
  }
  if (!printed) {
    cout << 0;
  }
  cout << ")";
}

// Karatsuba multiplication: O(n^log_2(3)) = O(n^1.585)
void multiply(ll p1[], ll p2[], ll r[], int deg)
{
  int rdeg = deg*2;
  fill(r, r+rdeg+1, 0);

  if (deg <= 15) {
    for (int n = 0; n <= rdeg; n++) {
      for (int i = 0; i <= min(n, deg); i++) {
	ll t1 = p1[i];
	ll t2 = (n-i <= deg) ? p2[n-i] : 0;
	r[n] += t1*t2;
      }
    }
    return;
  }
  
  int mid = (deg+1)/2;

  // p1 = h1 x^mid + l1
  // p2 = h2 x^mid + l2
  //
  // low = l1 * l2
  // hi = h1 * h2
  // cross = (h1+l1) * (h2+l2)
  //
  // p1*p2 = hi*x^(2*mid) + (cross - hi - lo)*x^mid + low

  int deg2 = max(mid, deg-mid);
  ll *low = new ll[2*(mid-1)+1 + 2*(deg-mid)+1 + 2*(deg2+1)+2*deg2+1];
  ll *hi = low + 2*(mid-1)+1;
  ll *t1 = hi + 2*(deg-mid)+1;
  ll *t2 = t1 + deg2+1;
  ll *cross = t2 + deg2+1;

  multiply(p1, p2, low, mid-1);
  copy(low, low+2*(mid-1)+1, r);
  
  multiply(p1+mid, p2+mid, hi, deg-mid);
  for (int i = 2*mid; i <= deg*2; i++) {
    r[i] += hi[i-2*mid];
  }

  copy(p1, p1+mid, t1);
  t1[mid] = 0;
  for (int i = mid; i <= deg; i++) {
    t1[i-mid] += p1[i];
  }
  copy(p2, p2+mid, t2);
  t2[mid] = 0;
  for (int i = mid; i <= deg; i++) {
    t2[i-mid] += p2[i];
  }
  multiply(t1, t2, cross, deg2);
  for (int i = 0; i <= 2*deg2; i++) {
    if (i <= 2*(deg-mid)) cross[i] -= hi[i];
    if (i <= 2*(mid-1)) cross[i] -= low[i];
    r[i+mid] += cross[i];
  }
  delete[] low;
}

bool solve()
{
  ll f[4][50001];

  int a, b, c;
  cin >> a >> b >> c;
  if (!a && !b && !c) return false;

  for (int i = 0; i < 4; i++) {
    copy(fmax, fmax+b+1, f[i]);
  }

  while (c--) {
    int rank;
    char suit;
    cin >> rank >> suit;
    f[suiti[suit]][rank] = 0;
  }

  ll newf[100001];
  multiply(f[0], f[1], newf, b);
  multiply(newf, f[2], f[0], b);
  multiply(f[0], f[3], newf, b);
  
  while (a <= b) {
    cout << newf[a++] << endl;
  }
  cout << endl;
  return true;
}

int main(void)
{
  // build a sieve

  // we will call 0 and 1 prime for this problem
  fill(prime, prime+50001, true);

  for (ll p = 2; p <= 50000; p++) {
    if (!prime[p]) continue;
    for (ll k = p*p; k <= 50000; k += p) {
      prime[k] = false;
    }
  }

  // the generating function with 1's at the composite powers
  for (int i = 0; i <= 50000; i++) {
    fmax[i] = (prime[i]) ? 0 : 1;
  }

  suiti['S'] = 0;
  suiti['H'] = 1;
  suiti['D'] = 2;
  suiti['C'] = 3;
  while (solve())
    ;

  return 0;
}
