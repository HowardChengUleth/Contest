#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, K;
  cin >> N >> K;

  map<string, set<int>> pos;
  set<string> matched;
  
  for (int i = 0; i < K; i++) {
    int C[2];
    string P[2];
    cin >> C[0] >> C[1] >> P[0] >> P[1];
    pos[P[0]].insert(C[0]);
    pos[P[1]].insert(C[1]);
    if (P[0] == P[1]) {
      matched.insert(P[1]);
    }
  }

  int known = 0;        // number of face down pairs known to match
  int unmatched = 0;    // number of face down cards without partners
  for (auto [ card, S ] : pos) {
    if (matched.count(card)) {
      continue;
    }
    if (S.size() == 2) {
      known++;
    } else {
      unmatched++;
    }
  }

  if (unmatched == N/2 - matched.size() - known) {
    // just open the unknown ones.  Each one will be matched to an unmatched
    // face down card
    known += unmatched;
  }

  // special case: if there are exactly 2 unopened card and there are no
  // unmatched, then the two are guarantted to match
  if (unmatched == 0 && N/2 - matched.size() - known == 1) {
    known++;
  }
  

  cout << known << endl;
  
  return 0;
}
