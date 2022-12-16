#include <bits/stdc++.h>

using namespace std;

map<string,int> node_name;

int node_index(string name)
{
  if (node_name.find(name) == node_name.end()) {
    int n = node_name.size();
    return node_name[name] = n;
  }
  return node_name[name];
}

vector<int> G[100];
int flow[100];

void read_input()
{
  node_index("AA");

  string line;
  while (getline(cin, line)) {
    replace(begin(line), end(line), ',', ' ');
    replace(begin(line), end(line), ';', ' ');
    replace(begin(line), end(line), '=', ' ');
    istringstream iss(line);
    string dummy;
    string valve, valve_to;
    iss >> dummy >> valve;

    int valve_idx = node_index(valve);
    iss >> dummy >> dummy >> dummy >> flow[valve_idx];
    iss >> dummy >> dummy >> dummy >> dummy;
    while (iss >> valve_to) {
      int to_idx = node_index(valve_to);
      G[valve_idx].push_back(to_idx);
    }
  }
}

typedef unsigned long long ull;

// memo[v][t][mask] = best we can get if we are at vertex v, with time t left,
// and mask being the ones already open
map<ull, int> memo[100][40];

int f(int v, int t, ull mask)
{
  auto &M = memo[v][t];
  if (M.find(mask) != M.end()) {
    return M[mask];
  }

  // no more time
  if (t == 0) {
    return 0;
  }

  int best = 0;
  
  // try opening the valve
  if (flow[v] > 0 && !(mask & (1ULL << v))) {
    best = max(best, f(v, t-1, mask | (1ULL << v)) + flow[v] * (t-1));
  }

  // don't open and just move
  for (auto w : G[v]) {
    best = max(best, f(w, t-1, mask));
  }
  
  return M[mask] = best;
}

int main()
{
  read_input();

  int ans = f(node_index("AA"), 30, 0);

  cout << ans << endl;
  
  return 0;
}
