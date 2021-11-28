#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld pi = acos(ld(-1.0));

ld a, b;
int N;

ld integral(ld theta)
{
  return 0.5 * (a*a*theta*theta*theta / 12 / pi / pi
		+ a * theta * theta * b / 2 / pi
		+ b * b * theta);
}

ld area(ld L, ld U)
{
  ld ans = integral(U) - integral(L);
  return ans;
}

int main()
{
  cin >> a >> b >> N;

  // area = 1/2 int(r(theta), theta = 0..2*pi)
  ld total = pi/3 * (a*a + 3*a*b + 3*b*b);
  ld slice = total / N;
  
  ld prev = 0.0;
  for (int i = 0; i < N-1; i++) {
    ld lo = prev, hi = 2*pi;
    while (hi - lo > 1e-15) {
      ld mid = (lo+hi)/2;
      if (area(prev, mid) < slice) {
	lo = mid;
      } else {
	hi = mid;
      }
    }
    
    cout << fixed << setprecision(15) << lo << endl;
    prev = (lo + hi)/2;
  }
  


  return 0;
}
