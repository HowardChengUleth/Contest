#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// the idea is to look at all possible cadence as D_i/C_j, sort the list, and
// check that the increase from one to the other is not too large.  The only
// trick is to do everything as integer arithmetic.

struct Gear
{
  ll C, D;

  Gear(ll CC = 1, ll DD = 1) : C{CC}, D{DD} {}

  bool operator<(const Gear &g) const
  {
    return D * g.C < C * g.D;
  }
};

int main()
{
  int N, M, P;
  cin >> N >> M >> P;

  int C[100], D[100];
  for (int i = 0; i < N; i++) {
    cin >> C[i];
  }
  for (int i = 0; i < M; i++) {
    cin >> D[i];
  }

  Gear G[10000];
  int k = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      G[k++] = Gear{C[i], D[j]};
    }
  }
  sort(G, G+k);

  //  100*(D1*C2 - D2*C1) <= D2*C1 * P
  for (int i = 0; i < k-1; i++) {
    if (100*(G[i+1].D*G[i].C - G[i].D*G[i+1].C) > G[i+1].C*G[i].D*P) {
      cout << "Time to change gears!" << endl;
      return 0;
    }
  }

  cout << "Ride on!" << endl;
  

  
  return 0;
}
