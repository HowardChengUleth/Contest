#include <bits/stdc++.h>

using namespace std;

vector<string> G;
int h, w;

int count_trees(int sr, int sc)
{
  int count = 0;
  int r = 0, c = 0;

  while (r < h) {
    if (G[r][c] == '#') {
      count++;
    }
    r += sr;
    c += sc;
    c %= w;
  }
  return count;
}

int main()
{
  string s;

  while (cin >> s) {
    G.push_back(s);
  }

  h = G.size();
  w = G[0].length();

  int sr[] = {1,1,1,1,2};
  int sc[] = {1,3,5,7,1};

  long long ans = 1;
  for (int i = 0; i < 5; i++) {
    cout << "A: " << count_trees(sr[i], sc[i]) << endl;
    ans *= count_trees(sr[i], sc[i]);
  }
  cout << ans << endl;


  return 0;
}
