#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> tx, ty;
vector<bool> alive;

const int MAX_N = 300'000;

typedef pair<int,int> pii;

// XbyY[v] contains set of X coordinates at y = v
// YbyX[v] contains set of Y coordiatess at x = v
map<int, set<pii>> XbyY, YbyX;

void handle(int t, char dir)
{
  if (!alive[t]) {
    cout << "ignore" << endl;
    return;
  }

  vector<int> kill;
  kill.reserve(N);

  set<pii> *M;
  set<pii>::iterator start, end;
  bool rev = false;
  
  switch (dir) {
  case 'N':
    M = &(YbyX[tx[t]]);
    start = M->lower_bound(pii(ty[t], MAX_N+1));
    end = M->end();
    break;
  case 'S':
    M = &(YbyX[tx[t]]);
    start = M->begin();
    end = M->upper_bound(pii(ty[t], 0));
    rev = true;
    break;
  case 'E':
    M = &(XbyY[ty[t]]);
    start = M->lower_bound(pii(tx[t], MAX_N+1));
    end = M->end();
    break;
  case 'W':
    M = &(XbyY[ty[t]]);
    start = M->begin();
    end = M->upper_bound(pii(tx[t], 0));
    rev = true;
    break;
  }

  while (start != end) {
    kill.push_back(start->second);
    ++start;
  }
  if (rev) {
    reverse(kill.begin(), kill.end());
  }
  
  cout << kill.size();
  for (auto team : kill) {
    XbyY[ty[team]].erase(pii(tx[team], team));
    YbyX[tx[team]].erase(pii(ty[team], team));
    alive[team] = false;
    cout << ' ' << team;
  }
  cout << endl;
}

int main()
{
  cin >> N >> M;
  alive.resize(N+1, true);
  tx.resize(N+1);
  ty.resize(N+1);

  for (int i = 1; i <= N; i++) {
    int x, y;
    cin >> x >> y;
    XbyY[y].emplace(x, i);
    YbyX[x].emplace(y, i);
    tx[i] = x;
    ty[i] = y;
  }

  for (int i = 0; i < M; i++) {
    int t;
    char dir;
    cin >> t >> dir;

    handle(t, dir);
  }
    

  return 0;
}
