#include <iostream>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

// an n-digit integer encoding where everyone is, and an int encoding which
// site has been searched.
typedef pair<int, int> State;

// map to canonical encoding for location of everyone (string of nondecreasing
// digits)
int canon[5][10000];

int deg[10];
int adj[10][40];

void move(State curr, State next, int index, int n,
	  queue<State> &q, map<State, int> &dist)
{
  if (index == n) {
    next.first = canon[n][next.first];
    if (dist.find(next) == dist.end()) {
      dist[next] = dist[curr] + 1;
      q.push(next);
    }
    return;
  }

  int pos = curr.first;
  int mult = 1;
  for (int i = 0; i < index; i++) {
    pos /= 10;
    mult *= 10;
  }
  pos %= 10;

  for (int i = 0; i < deg[pos]; i++) {
    int v = adj[pos][i];
    State next2 = next;
    next2.first += (v - pos)*mult;
    next2.second |= 1 << v;
    move(curr, next2, index+1, n, q, dist);
  }
}


bool solve()
{
  int s, n, p;
  cin >> s >> n >> p;
  if (!s) return false;

  fill(deg, deg + 10, 0);
  for (int i = 0; i < p; i++) {
    char a, b;
    cin >> a >> b;
    int u = a - 'A';
    int v = b - 'A';

    adj[u][deg[u]++] = v;
    adj[v][deg[v]++] = u;
  }
  
  // 0 = 'A', 1 = 'B', etc.

  // everyone starts at A, and A is already searched
  map<State, int> dist;
  queue<State> q;
  
  State start = make_pair(0, 1);
  dist[start] = 0;
  q.push(start);
  while (!q.empty()) {
    State curr = q.front();
    q.pop();
    if (curr.second == (1 << s) - 1) {
      cout << dist[curr] << endl;
      break;
    }

    // now move everyone
    move(curr, curr, 0, n, q, dist);
  }

  return true;
}

int main(void)
{
  for (int n = 1; n <= 4; n++) {
    for (int i = 0; i < 10000; i++) {
      canon[n][i] = 0;
      int t = i;
      int A[4];
      for (int j = 0; j < n; j++) {
	A[j] = t % 10;
	t /= 10;
      }
      sort(A, A+n);
      for (int j = 0; j < n; j++) {
	canon[n][i] *= 10;
	canon[n][i] += A[j];
      }
    }
  }

  
  while (solve())
    ;
  return 0;
}
