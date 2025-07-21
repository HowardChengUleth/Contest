#include <bits/stdc++.h>

using namespace std;


// the fact that each value number is the sum of previous two means that we
// should always take the largest fibonacci number possible greedily.  Not
// using it will only end up using more smaller numbers to make up that sum.

int main()
{
  vector<int> fib;
  fib.push_back(1);
  fib.push_back(2);

  while (true) {
    int next = fib[fib.size()-1] + fib[fib.size()-2];
    if (next > 1'000'000'000) {
      break;
    }
    fib.push_back(next);
  }

  int n;
  cin >> n;

  vector<int> ans;
  for (int i = fib.size()-1; i >= 0; i--) {
    while (fib[i] <= n) {
      n -= fib[i];
      ans.push_back(fib[i]);
    }
  }

  reverse(begin(ans), end(ans));
  for (auto x : ans) {
    cout << x << ' ';
  }
  cout << endl;

  return 0;
}
