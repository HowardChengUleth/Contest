#include <bits/stdc++.h>

using namespace std;

void scan_left(const vector<int> &h, vector<int> &left)
{
  int n = h.size();
  left.resize(n, INT_MAX);

  stack<int> S;
  for (int i = 0; i < n; i++) {
    while (!S.empty() && h[S.top()] < h[i]) {
      S.pop();
    }
    if (!S.empty()) {
      left[i] = i - S.top();
    }
    S.push(i);
  }
}

int main()
{
  int n;
  cin >> n;

  vector<int> h(n), a(n, -2), left, right;
  for (auto &x : h) {
    cin >> x;
  }

  scan_left(h, left);
  reverse(begin(h), end(h));
  scan_left(h, right);
  reverse(begin(h), end(h));
  reverse(begin(right), end(right));

  for (int i = 0; i < n; i++) {
    if (i == 0 || i == n-1 || h[i-1] >= h[i] || h[i+1] >= h[i]) {
      a[i] = 0;
    } else {
      int temp = min(left[i], right[i]);
      if (temp == INT_MAX) {
	a[i] = -1;
      } else {
	a[i] = temp;
      }
    }
  }

  for (auto &x : a) {
    cout << x << ' ';
  }
  cout << endl;
  
  return 0;
}
