// You can think of this as a sum of "nim games".  Each stone can be moved
// independently of the others and can in fact be considered independently.
// It is well known in game theory that if we work out a "nimber" of each
// game, then the nimber of the sum of these games is the bitwise XOR of
// the nimbers.  The first player wins iff the nimber is nonzero.
//
// To compute the nimber of each individual game (stone), it is enough to
// consider where the stone is (and it can be in one of n places).  For
// each game, the nimber is calculated by looking at the set of all nimbers
// for the next moves and finding the smallest nonnegative integer not in
// this set (this is the "mex rule").
//
#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
pair<int,int> edge[10000];
pair<int,int> adj[1000];

// nimber of the game if we were to have only one stone placed on the i-th node
int nimber[1000];

void compute(int i)
{
  // we have already computed the nimber for that game
  if (nimber[i] >= 0) return;

  int deg = adj[i].second - adj[i].first;
  
  // if we can't push them anywhere, 1st player loses
  if (deg == 0) {
    nimber[i] = 0;
    return;
  }

  // try pushing all possible ways and take mex
  int vals[1000];
  for (int k = 0; k < deg; k++) {
    int e_index = adj[i].first + k;
    int to = edge[e_index].second;
    compute(to);
    vals[k] = nimber[to];
  }

  // find mex value
  sort(vals, vals+deg);
  int prev = -1;
  for (int k = 0; k < deg; k++) {
    if (vals[k] > prev+1) {
      nimber[i] = prev+1;
      return;
    }
    prev = vals[k];
  }
  nimber[i] = prev+1;
    
}

bool do_case()
{
  // read input
  cin >> n >> m;
  if (!n && !m) return false;

  for (int i = 0; i < m; i++) {
    cin >> edge[i].first >> edge[i].second;
  }
  sort(edge, edge+m);
  for (int i = 0; i < n; i++) {
    adj[i] = make_pair(0,0);
  }

  for (int i = 0; i < m; i++) {
    if (i == 0 || edge[i].first != edge[i-1].first) {
      adj[edge[i].first].first = i;
    }
    if (i == m-1 || edge[i].first != edge[i+1].first) {
      adj[edge[i].first].second = i+1;
    }
  }

  fill(nimber, nimber+n, -1);

  int nim_sum = 0;

  // each stone can be considered as a nim game independently.  Since the
  // nim sum is XOR, we only have to do something (one thing) if the number
  // of stones is odd.  The even numbers will cancel each other when doing
  // XOR
  for (int i = 0; i < n; i++) {
    int s;
    cin >> s;
    if (s % 2 == 0) continue;
    compute(i);
    nim_sum ^= nimber[i];
  }

  if (nim_sum) {
    cout << "First" << endl;
  } else {
    cout << "Second" << endl;
  }

  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
