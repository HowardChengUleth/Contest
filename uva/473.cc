#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve()
{
  int n, t, m;
  cin >> n >> t >> m;

  vector<int> len(n);
  for (int i = 0; i < n; i++) {
    if (i) {
      char ch;
      cin >> ch;
    }
    cin >> len[i];
  }

  vector<int> table[2];
  table[0].resize(m*t+1);
  table[1].resize(m*t+1);

  int curr = 0;

  fill(table[curr].begin(), table[curr].end(), -1);
  table[curr][0] = 0;

  for (int i = 0; i < n; i++) {
    int next = 1 - curr;
    fill(table[next].begin(), table[next].end(), -1);

    for (unsigned int j = 0; j < table[curr].size(); j++) {
      if (table[curr][j] < 0) continue;

      // don't add the song
      table[next][j] = max(table[curr][j], table[next][j]);

      // try adding
      int left = t - j%t;
      int total;
      if (left < len[i]) {
	total = j + left + len[i];
      } else {
	total = j + len[i];
      }
      if (total > m*t) continue;
      table[next][total] = max(table[curr][j]+1, table[next][total]);
    }
    curr = next;
  }

  cout << *max_element(table[curr].begin(), table[curr].end()) << endl;
  
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    if (i) cout << endl;
    solve();
  }
  return 0;
}
