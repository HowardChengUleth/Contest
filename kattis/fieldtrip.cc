#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  int total = 0;
  vector<int> sec(N);
  for (auto &x : sec) {
    cin >> x;
    total += x;
  }

  if (total % 3 != 0) {
    cout << -1 << endl;
    return 0;
  }

  int target = total/3;
  partial_sum(begin(sec), end(sec), begin(sec));

  int i = find(begin(sec), end(sec), target) - begin(sec) + 1;
  int j = find(begin(sec), end(sec), 2*target) - begin(sec) + 1;

  if (i > N || j > N) {
    cout << -1 << endl;
  } else {
    cout << i << ' ' << j << endl;
  }

  return 0;
}
