#include <bits/stdc++.h>

using namespace std;

int main()
{
  vector<int> pos;

  string line;
  cin >> line;
  replace(begin(line), end(line), ',', ' ');
  istringstream iss(line);

  int x;
  while (iss >> x) {
    pos.push_back(x);
  }
  sort(begin(pos), end(pos));
  int n = pos.size();
  int med = n/2;

  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans += abs(pos[i] - pos[med]);
  }

  cout << ans << endl;

  
  return 0;
}
