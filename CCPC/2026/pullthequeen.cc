//
// This is classic DP
//
// A few observations:
//
// - the deck will always have 4 queens and 4 kings if the game keeps going
// - So we only need to keep track of:
//   - how many turns are left
//   - who's turn it is (in my code, my "turn" is only one player drawing a
//                       card, not both)
//   - how many cards are left
//
// So this is DP with states determined by 3 components.
//

#include <bits/stdc++.h>

using namespace std;

double memo[101][2][53];

// probability of winning with specified number of turns (M) and number of
// cards left.  "win" means it is the turn of the player we are interested
// in.
double f(int M, bool win, int cards)
{
  if (M == 0 || cards == 0) {
    // no way to draw a queen
    return 0.0;
  }
  double &prob = memo[M][win][cards];
  if (prob >= 0.0) {
    // already computed
    return prob;
  }
  
  prob = 0.0;
  prob += 4.0/cards * f(M-1, !win, cards);     // draw a king
  prob += (cards-8.0) / cards * f(M-1, !win, cards-1);  // draw something else
  if (win) {
    prob += 4.0 / cards;       // draw a queen, win the game
  }
  return prob;
}

void solve()
{
  char p;
  int M;
  cin >> p >> M;

  for (int i = 0; i <= 2*M; i++) {
    for (int j = 0; j < 2; j++) {
      fill(memo[i][j], memo[i][j] + 53, -1.0);
    }
  }
  cout << fixed << setprecision(15) << f(2*M, p == 'A', 52) << endl;
}


int main()
{
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    solve();
  }

  return 0;
}
