#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<string> c;
bool bad[12][12];
bool first;
int firstperm[12];

int search(int perm[], int index)
{
  if (index >= N) {
    if (first ||
	lexicographical_compare(perm, perm+N, firstperm, firstperm+N)) {
      copy(perm, perm+N, firstperm);
      first = false;
    }
    return 1;
  }

  int ans = 0;
  for (int i = index; i < N; i++) {
    swap(perm[index], perm[i]);
    bool good = (index == 0) || !bad[perm[index-1]][perm[index]];
    if (good) {
      ans += search(perm, index+1);
    }
    swap(perm[index], perm[i]);
  }
  return ans;
}

void solve()
{
  cin >> N;

  c.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> c[i];
    fill(bad[i], bad[i]+N, false);
  }

  cin >> M;
  for (int i = 0; i < M; i++) {
    string s1, s2;
    cin >> s1 >> s2;
    int i1 = find(begin(c), end(c), s1) - begin(c);
    int i2 = find(begin(c), end(c), s2) - begin(c);
    bad[i1][i2] = bad[i2][i1] = true;
  }

  int perm[12];
  iota(perm, perm+N, 0);

  first = true;
  cout << search(perm, 0) << endl;
  for (int i = 0; i < N; i++) {
    cout << c[firstperm[i]] << ' ';
  }
  cout << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
