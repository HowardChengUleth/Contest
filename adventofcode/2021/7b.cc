#include <bits/stdc++.h>

using namespace std;

vector<int> pos;
int n;

int test(int p)
{
  int ans = 0;
  for (auto x : pos) {
    int diff = abs(x - p);
    ans += diff * (diff+1) / 2;
  }
  return ans;
}

int main()
{

  string line;
  cin >> line;
  replace(begin(line), end(line), ',', ' ');
  istringstream iss(line);

  int x;
  while (iss >> x) {
    pos.push_back(x);
  }
  sort(begin(pos), end(pos));
  n = pos.size();

  int ans = INT_MAX;
  for (int t = pos[0]; t <= pos[n-1]; t++) {
    ans = min(ans, test(t));
  }

  cout << ans << endl;
  
  return 0;
}
