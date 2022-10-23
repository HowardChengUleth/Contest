#include <bits/stdc++.h>

using namespace std;

int memo[1 << 15];


int index(map<string,int> &nlist, const string &name)
{
  if (nlist.find(name) == nlist.end()) {
    int size = nlist.size();
    return nlist[name] = size;
  }
  return nlist[name];
}

bool f(int mask, const vector<int> &triples, int start = 0)
{
  int &ans = memo[mask];
  if (ans != -1) {
    return ans;
  }
  if (!mask) return true;

  for (int i = start; i < triples.size(); i++) {
    int mask2 = triples[i];
    if ((mask & mask2) != mask2) continue;
    if (f(mask - mask2, triples, i+1)) {
      return ans = true;
    }
  }
  
  return ans = false;
}						\

bool solve()
{
  int m;
  cin >> m;
  if (!m) {
    return false;
  }

  bool good[15][15] = { false };
  
  map<string,int> nlist;
  for (int i = 0; i < m; i++) {
    string n1, n2;
    cin >> n1 >> n2;
    int i1 = index(nlist, n1);
    int i2 = index(nlist, n2);

    good[i1][i2] = good[i2][i1] = true;
  }

  int n = nlist.size();
  if (n % 3) {
    cout << "impossible" << endl;
    return true;
  }

  vector<int> triples;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      for (int k = j+1; k < n; k++) {
	if (good[i][j] && good[j][k] && good[i][k]) {
	  triples.push_back((1 << i) | (1 << j) | (1 << k));
	}
      }
    }
  }

  fill(memo, memo + (1 << n), -1);
  cout << (f((1 << n) - 1, triples) ? "possible" : "impossible") << endl;

  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
