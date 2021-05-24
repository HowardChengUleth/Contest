#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> w1, w2;

bool check(const vector<int> &w, int g)
{
  int num = 0, last = -1;
  for (int i = 0; i < w.size(); i++) {
    if (w[i] <= g) continue;
    if (num % 2 == 1) {
      if (w[i] != last) return false;
    }
    num++;
    last = w[i];
  }
  return num % 2 == 0;
}

bool possible(int g)
{
  return check(w1, g) && check(w2, g);
}

int main()
{
  cin >> n;
  w1.resize(n);
  w2.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> w1[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> w2[i];
  }

  if (possible(0)) {
    cout << 0 << endl;
    return 0;
  }
  
  int lo = 0,
    hi = max(*max_element(begin(w1), end(w1)),
	     *max_element(begin(w2), end(w2)));

  while (hi - lo > 1) {
    int mid = lo + (hi-lo)/2;
    if (possible(mid)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }

  cout << hi << endl;
  
  return 0;
}
