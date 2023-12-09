#include <bits/stdc++.h>

using namespace std;

int extrapolate(string line)
{
  istringstream iss(line);
  vector<int> seq;

  int x;
  while (iss >> x) {
    seq.push_back(x);
  }

  vector<vector<int>> table;
  table.push_back(seq);

  while (count(begin(seq), end(seq), 0) != (int)seq.size()) {
    vector<int> next;
    for (int i = 0; i < (int)seq.size()-1; i++) {
      next.push_back(seq[i+1] - seq[i]);
    }
    table.push_back(next);
    seq = next;
  }

  for (auto &v : table) {
    reverse(begin(v), end(v));
  }

  table.back().push_back(0);
  for (int row = table.size()-2; row >= 0; row--) {
    table[row].push_back(table[row].back() - table[row+1].back());
  }

  for (auto &v : table) {
    reverse(begin(v), end(v));
  }


  
  for (auto v : table) {
    for (auto x : v) {
      cout << x << ' ';
    }
    cout << endl;
  }

  return table[0][0];
}

int main()
{
  string str;

  int ans = 0;
  while (getline(cin, str)) {
    ans += extrapolate(str);
  }
      
  cout << ans << endl;

  return 0;
}
