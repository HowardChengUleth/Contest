#include <bits/stdc++.h>

using namespace std;

//
// The fact that the necklace doesn't change after a rotation by k positions
// means that the positions 0, k, 2k, 3k, etc. mod len must have the same
// character.  So to test for a particular length, you can just mark those
// positions until it cycles, and greedily put the character that is frequent
// enough to cover those positions.


int n, k;
string s;
int freq[256];

int DFS(int v, int len, bool visited[])
{
  visited[v] = true;
  int next = (v+k) % len;

  int ans = 1;
  if (!visited[next]) {
    ans += DFS(next, len, visited);
  }
  return ans;
}

bool check(int len)
{
  bool visited[2000] = {false};
  for (int i = 0; i < len; i++) {
    if (visited[i]) continue;
    int cycle = DFS(i, len, visited);

    int best_i = -1;
    for (int i = 'a'; i <= 'z'; i++) {
      if (freq[i] < cycle) continue;
      if (best_i == -1 || freq[i] < freq[best_i]) {
	best_i = i;
      }
    }
    if (best_i < 0) return false;
    freq[best_i] -= cycle;
  }
  return true;
}

void solve()
{
  cin >> n >> k;
  cin >> s;
  fill(freq, freq+256, 0);
  for (auto c : s) {
    freq[c]++;
  }

  int freq2[256];
  copy(freq, freq+256, freq2);
  
  for (int len = n; len >= 1; len--) {
    copy(freq2, freq2+256, freq);
    if (check(len)) {
      cout << len << endl;
      return;
    }
  }
}

int main()
{
  int t;
  cin >> t;
  while (t--)
    solve();

  return 0;
}
