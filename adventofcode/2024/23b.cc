#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef set<string> ss;

map<string, ss> G;
vector<string> V;
int N;

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

  sort(begin(V), end(V));
  N = V.size();
}

vector<int> best_clique;

void search(vector<int> &clique, int next)
{
  if (clique.size() > best_clique.size()) {
    best_clique = clique;
  }
  
  if (next >= N) {
    return;
  }

  for (int i = next; i < N; i++) {
    bool good = true;
    for (auto vi : clique) {
      good &= G[V[vi]].count(V[i]) > 0;
      if (!good) break;
    }
    if (good) {
      clique.push_back(i);
      search(clique, i+1);
      clique.pop_back();
    }
  }
}

int main()
{
  read_graph();

  ll ans = 0;

  map<int,int> deg_freq;
  for (auto [ s, adj ] : G) {
    deg_freq[adj.size()]++;
  }

  for (auto [ deg, freq ] : deg_freq) {
    cout << "deg = " << deg << " x" << freq << endl;
  }

  for (int i = 0; i < N; i++) {
    vector<int> clique;
    clique.push_back(i);
    search(clique, i+1);
  }

  for (auto vi : best_clique) {
    cout << V[vi] << ',';
  }
  cout << endl;

  return 0;
}
