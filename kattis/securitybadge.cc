#include <bits/stdc++.h>

using namespace std;

struct Edge
{
  int v, lo, hi;
  Edge(int b, int x, int y) : v{b}, lo{x}, hi{y} {}
};

int N, L, B;
int S, D;

vector<Edge> G[1001];
vector<int> badge;

bool reachable(int b)
{
  bool vis[1001] = {false};
  queue<int> q;

  vis[S] = true;
  q.push(S);

  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    for (auto e : G[curr]) {
      if (e.lo <= b && b <= e.hi && !vis[e.v]) {
	vis[e.v] = true;
	q.push(e.v);
      }
    }
  }

  return vis[D];
}


int main()
{
  cin >> N >> L >> B;
  cin >> S >> D;

  for (int i = 0; i < L; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    G[a].emplace_back(b,x,y);
    badge.push_back(x);
    badge.push_back(y+1);
  }

  sort(begin(badge), end(badge));
  badge.resize(unique(begin(badge), end(badge)) - begin(badge));

  int ans = 0;
  int prev = 0;
  bool prev_pass = false;
  for (auto b : badge) {
    if (prev_pass) {
      ans += b - prev;
    }
    prev = b;
    prev_pass = reachable(b);
  }
  cout << ans << endl;
  return 0;
}
