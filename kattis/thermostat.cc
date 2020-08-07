#include <bits/stdc++.h>

using namespace std;

// idea is to basically write the conversion function from each unit
// to celsius as f(t) = m*t + b.  Using the fact that f(A) = 0 and f(B) = 100
// we can solve for m and b.  Then we can just convert x to celsius with f_x,
// and then convert celsius to y with f_y^(-1).  Use fraction class


#include <iostream>
#include <cstdlib>
using namespace std;

typedef long long ll;
// Note: Applying operations to reduced fractions should yield a reduced answer
//       Make sure you reduce the fraction when you store it into the structure.
//  EXCEPT: 0 may be 0/x until reduce is called (then changed to 0/1)
typedef long long ll;
struct frac{  ll num,den; };

ll gcd(ll a, ll b)
{
  if (a < 0) return gcd(-a, b);
  if (b < 0) return gcd(a, -b);
  if (b == 0) return a;
  return gcd(b, a%b);
}

frac make_frac(ll n,ll d){ frac f; f.num = n,f.den = d; return f; }

frac reduce(frac a){
  if(a.num == 0) return make_frac(0,1); if(a.den < 0) { a.num *= -1; a.den *= -1; }
  ll g = gcd(a.num,a.den); return make_frac(a.num/g,a.den/g);
}
frac recip(frac a){ return reduce(make_frac(a.den,a.num)); }

frac operator+(frac a,frac b){
  ll g = gcd(a.den,b.den);
  return reduce(make_frac(a.num*(b.den/g) + b.num*(a.den/g), (a.den/g)*b.den));
}
frac operator-(frac a,frac b){ return a + make_frac(-b.num,b.den); }
frac operator*(frac a,frac b){
  ll g1 = gcd(a.num,b.den), g2 = gcd(a.den,b.num);
  return make_frac((a.num / g1) * (b.num / g2),(a.den / g2) * (b.den / g1));
}
frac operator/(frac a,frac b){ return a * recip(b); } // Watch division by 0

bool operator==(frac a,frac b){
  a=reduce(a); b=reduce(b);
  return a.num==b.num && a.den==b.den;
}

// Choose one. First one may overflow. Second one has rounding errors.
bool operator<(frac a,frac b){ return (a.num*b.den) < (b.num*a.den); }

ostream &operator<<(ostream &os, frac f)
{
  f = reduce(f);
  return os << f.num << '/' << f.den;
}

int main()
{
  int N, Q;
  cin >> N >> Q;

  ll a[100], b[100];
  for (int i = 0; i < N; i++) {
    cin >> a[i] >> b[i];
  }

  for (int i = 0; i < Q; i++) {
    ll x, y, v;
    cin >> x >> y >> v;
    x--; y--;
    
    // change to celsius
    frac m1{100, b[x]-a[x]};
    frac b1 = m1 * make_frac(-a[x], 1);

    frac celsius = m1 * make_frac(v, 1) + b1;

    // convert to y
    frac m2{100, b[y]-a[y]};
    frac b2 = m2 * make_frac(-a[y], 1);

    frac ans = (celsius - b2) / m2;
    cout << ans << endl;
    
  }

  return 0;
}
