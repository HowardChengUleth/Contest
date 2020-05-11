// The idea is this: we do exhaustive search at each step, so each
// player will try all possible moves.  Note that the "state" of the
// game depends only on which nodes have been exhausted.  If we arrive
// at exactly the same subset of exhausted nodes, the result of the
// remaining game is always going to be the same from this point on.
// So all we have to do is do the computation for each possible subset
// of exhausted states to get the answer (obviously the start is an
// empty set).
//

#include <iostream>
#include <algorithm>

using namespace std;

int n;

// best scores if we start with a certain subset of exhausted vertices,
// first component = best score for first player
// second component = best score for second player
//
// subset of n things (n <= 16) is indexed by an n-bit integer where
// the i-th bit indicates whether the i-th vertex is exhausted
pair<int,int> table[(1 << 16)];
bool init[(1 << 16)];
bool graph[16][16];
int profit[16];

void compute(int subset)
{
  if (init[subset]) {
    // already computed
    return;
  }

  for (int i = 0; i < n; i++) {
    int next_set = (subset | (1 << i));
    if (subset == next_set) continue;  // that move has been made already
    
    bool can_put = (subset == 0);    // first move can be anywhere

    // check whether I am adjacent to someone already exhausted
    for (int j = 0; j < n && !can_put; j++) {
      can_put |= ((subset & (1 << j)) && graph[i][j]);
    }
    if (!can_put) continue;

    // compute the next one recursively
    compute(next_set);
    pair<int, int> r = table[next_set];

    // need to swap the scores, because first player in the next move is
    // actually the second player for this move
    swap(r.first, r.second);

    // add the score for this move
    r.first += profit[i];

    // if the new score is better than what I have found for this subset
    // so far, replace
    if (!init[subset] || r.first > table[subset].first ||
	(r.first == table[subset].first && r.second < table[subset].second)) {
      table[subset] = r;
      init[subset] = true;
    }
  }
}

bool do_case()
{
  cin >> n;
  if (!n) return false;

  // read input
  for (int i = 0; i < n; i++) {
    cin >> profit[i];
  }

  for (int i = 0; i < n; i++) {
    fill(graph[i], graph[i]+n, false);
  }

  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    graph[a][b] = graph[b][a] = true;
  }

  fill(init, init + (1 << n), false);

  // game over == subset with all vertices exhausted (all 1's)
  table[(1 << n) - 1] = make_pair(0, 0);
  init[(1 << n) - 1] = true;
  
  // compute with the empty set
  compute(0);
  pair<int, int> &result = table[0];

  // print the results
  if (result.first == result.second) {
    cout << "Tie game! " << result.first << ' ' << "all." << endl;
  } else {
    if (result.first > result.second) {
      cout << "First ";
    } else {
      cout << "Second ";
    }
    cout << "player wins! " << max(result.first, result.second)
	 << " to " << min(result.first, result.second) << "." << endl;
  }
  
  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
