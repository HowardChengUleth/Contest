#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef set<string> ss;

map<string, ss> G;
vector<string> V;

void read_graph()
{
  string line;
  while (getline(cin, line)) {
    string v1 = line.substr(0,2);
    string v2 = line.substr(3,2);
    G[v1].insert(v2);
    G[v2].insert(v1);
  }

  for (auto [v, adj] : G) {
    V.push_back(v);
  }
}

int main()
{
  read_graph();

  int ans = 0;
  for (int i = 0; i < (int)V.size(); i++) {
    auto v1 = V[i];
    for (int j = i+1; j < (int)V.size(); j++) {
      auto v2 = V[j];
      if (G[v1].count(v2) == 0) continue;
      for (int k = j+1; k < (int)V.size(); k++) {
	auto v3 = V[k];
	if (G[v1].count(v3) == 0 || G[v2].count(v3) == 0) continue;
	if (v1[0] == 't' || v2[0] == 't' || v3[0] == 't')
	  ans++;
      }
    }
  }

  cout << ans << endl;

  return 0;
}
