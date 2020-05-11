#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;
using namespace std::rel_ops;

struct State
{
  int vol[3];

  State(int v1, int v2, int v3)
  {
    vol[0] = v1;
    vol[1] = v2;
    vol[2] = v3;
  }

  State(const State &s)
  {
    copy(s.vol, s.vol+3, vol);
  }

  bool operator<(const State &s) const
  {
    return lexicographical_compare(vol, vol+3, s.vol, s.vol+3);
  }
    
};

typedef pair<int, State> pis;

void solve(int a, int b, int c, int d)
{
  map<State, int> dist;
  priority_queue<pis, vector<pis>, greater<pis> > pq;

  int cap[3];
  cap[0] = a;
  cap[1] = b;
  cap[2] = c;
  
  State init(0, 0, c);
  dist[init] = 0;
  pq.push(make_pair(0, init));

  int best_d = 0;
  State best_state = init;

  while (!pq.empty()) {
    State curr = pq.top().second;
    pq.pop();

    for (int i = 0; i < 3; i++) {
      if (curr.vol[i] > d) continue;

      // if we see a better d, we can just copy the state without comparing
      // distances because we always see the closest one first.
      if (curr.vol[i] > best_d) {
	best_d = curr.vol[i];
	best_state = curr;
      }
    }
    if (best_d == d) {
      // we can quit now
      break;
    }

    // try pouring in all possible way
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
	if (i == j) continue;

	// pour from i to j
	int amt = min(curr.vol[i], cap[j] - curr.vol[j]);
	if (amt == 0) continue;

	State next = curr;
	next.vol[i] -= amt;
	next.vol[j] += amt;

	if (dist.find(next) != dist.end()) continue;
	dist[next] = dist[curr] + amt;
	pq.push(make_pair(dist[next], next));
      }
    }
  }

  cout << dist[best_state] << ' ' << best_d << endl;
}

int main(void)
{
  int T;
  cin >> T;

  while (T-- > 0) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    solve(a, b, c, d);
  }
  return 0;
}
