#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
ll m, a, c, x0;
vector<ll> x;


bool search(int item)
{
  int lo = 0, hi = n-1;
  while (lo <= hi) {
    int mid = (lo + hi)/2;
    if (x[mid] == item) return true;
    if (x[mid] < item) {
      lo = mid+1;
    } else {
      hi = mid-1;
    }
  }

  return false;
}

int main()
{
  cin >> n >> m >> a >> c >> x0;
  x.resize(n);
  ll prev = x0;
  for (int i = 0; i < n; i++) {
    x[i] = ((a * prev) % m + c) % m;
    prev = x[i];
  }

  int count = 0;
  for (int i = 0; i < n; i++) {
    if (search(x[i])) {
      count++;
    }
  }

  cout << count << endl;
  return 0;
}
