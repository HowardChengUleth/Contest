//
// This is dynamic programming.  First, we sort the players by power level.
// The tie-breaking condition actually does not matter at all because we
// are asking for the max coins someone can get, not who gets the max coins.
//
// We ask the question: if p is the winner, what is the max it can win.
//
// First, notice that if p is the winner, no one with a higher ranking is
// involved with the duels.  So we only need to look at the ones with lower
// ranking.
//
// Player p can duel directly with p-1, p-2, ... until the power level is
// too low (difference > M).  If q is the player lowest ranked player that
// p directly duels with, he can also duel directly with q+1, ..., p-1 and
// take their coins directly.  So
//
//   f(p) = f(q) + C[q+1] + ... + C[p-1], and we maximize this over all q
//
// Note that we do not want to recurse on f(q+1), ... f(p-1) because they
// may end up getting some of the coins that q was going to get from its
// other duels.  Whatever q+1 can get indirectly, q could have gotten.
//
// O(N^2) with DP.

#include <bits/stdc++.h>

using namespace std;

int N, M;

int memo[1001];

// assuming players are sorted by power level, what is the max number of
// coins player p can get
int f(int p, const vector<pair<int,int>> &player)
{
  int &ans = memo[p];
  if (ans >= 0) {
    return ans;
  }
  
  ans = player[p].second;     // can always get their own

  // they can only duel people lower than or equal to them (lower in the
  // ranking).  If q < p is the lowest player p directly duels, then
  // p can also duel q+1, ..., p-1 directly and take their coins
  int total = player[p].second;
  for (int q = p-1; q >= 0 && player[p].first - player[q].first <= M; q--) {
    ans = max(ans, total + f(q, player));
    total += player[q].second;
  }
  return ans;
}

int main()
{
  cin >> N >> M;
  
  // <P, C>
  vector<pair<int,int>> player(N);
  for (auto &[P, C] : player) {
    cin >> C >> P;
  }

  // we don't really care about tie-breaking: it doesn't matter since
  // we don't need to know who gets the max
  sort(begin(player), end(player));

  fill(memo, memo+N+1, -1);
  
  int ans = 0;
  for (int p = 0; p < N; p++) {
    ans = max(ans, f(p, player));
  }
  
  cout << ans << endl;


  return 0;
}
