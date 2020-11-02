#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n;
map<ll, bool> win;

bool f(ll p) {
  if (win.find(p) != win.end()) {
    return win[p];
  }
  if (p >= n) {
    return win[p] = false;
  }

  for (int k = 2; k <= 9; k++) {
    if (!f(k*p)) {
      return win[p] = true;
    } 
  }
  return win[p] = false;
}

int main()
{
  while (cin >> n) {
    win.clear();
    if (f(1)) {
      cout << "Stan wins." << endl;
    } else {
      cout << "Ollie wins." << endl;
    }
  }

  return 0;
}
