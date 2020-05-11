#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
vector<int> freq[2][256];
vector<pii> ans;
int n;

void match(char c1, char c2)
{
  int t = min(freq[0][c1].size(), freq[1][c2].size());
  while (t--) {
    ans.emplace_back(freq[0][c1].back(), freq[1][c2].back());
    freq[0][c1].pop_back();
    freq[1][c2].pop_back();
  }
}

int main()
{
  cin >> n;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < n; j++) {
      char c;
      cin >> c;
      freq[i][c].push_back(j+1);
    }
  }

  for (int i = 'a'; i <= 'z'; i++) {
    match(i, i);
    match('?', i);
    match(i, '?');
  }
  match('?', '?');
  
  cout << ans.size() << endl;
  for (auto p : ans) {
    cout << p.first << ' ' << p.second << endl;
  }
  
  return 0;
}
