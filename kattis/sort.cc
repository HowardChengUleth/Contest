#include <bits/stdc++.h>

using namespace std;

map<int,int> freq;
map<int,int> first;

int main()
{
  int N, C;
  cin >> N >> C;

  for (int i = 0; i < N; i++) {
    int val;
    cin >> val;
    freq[val]++;

    if (first.find(val) == first.end()) {
      first[val] = i;
    }
  }

  vector<tuple<int,int,int>> v;
  for (auto [val, f] : freq) {
    v.emplace_back(-f, first[val], val);
  }
  sort(begin(v), end(v));
  for (auto [ d1, d2, val ] : v) {
    for (int i = 0; i < -d1; i++) {
      cout << val << ' ';
    }
  }
  cout << endl;
  
  
  return 0;
}
