#include <iostream>
#include <algorithm>

using namespace std;

bool solve()
{
  int n, d, r;
  cin >> n >> d >> r;
  if (!n && !d && !r) return false;

  int am[100], pm[100];
  for (int i = 0; i < n; i++) {
    cin >> am[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> pm[i];
  }

  sort(am, am+n);
  sort(pm, pm+n);

  int total = 0;
  for (int i = 0; i < n; i++) {
    int t = am[i] + pm[n-1-i];
    if (t > d) {
      total += (t-d)*r;
    }
  }

  cout << total << endl;
  return true;
}

int main(void)
{
  while (solve())
    ;

  return 0;
}
