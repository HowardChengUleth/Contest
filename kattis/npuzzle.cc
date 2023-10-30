#include <bits/stdc++.h>

using namespace std;

const string solved[] = {
  "ABCD",
  "EFGH",
  "IJKL",
  "MNO."
};

pair<int,int> find_solved(char c)
{
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (solved[i][j] == c) {
	return make_pair(i, j);
      }
    }
  }

  assert(false);
}

int main()
{
  string config[4];
  for (int i = 0; i < 4; i++) {
    cin >> config[i];
  }

  int ans = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (config[i][j] == '.') continue;
      auto coord = find_solved(config[i][j]);
      ans += abs(coord.first - i) + abs(coord.second - j);
    }
  }

  cout << ans << endl;

  return 0;
}
