#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;
typedef long double ld;

int main(void)
{
  int K;
  cin >> K;
  while (K--) {
    ll n;
    cin >> n;

    ld a = 0.5;
    ld b = 0.5;
    ld c = -n;
    cout << (ll)floor((-b + sqrt(b*b-4*a*c))/(2*a)) << endl;
  }

  return 0;
}
