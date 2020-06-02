#include <bits/stdc++.h>

using namespace std;

// DP on number of points obtained so far and number of each card
// used.  No need to remember whose turn it is because it can be determined.
//
// Number of states is 5^6 * 32

typedef pair<vector<int>, int> State;

map<State, int> winner;

// 0 = A, 1 = B
int f(State s) {
  if (winner.find(s) != winner.end()) {
    return winner[s];
  }

  auto v = s.first;
  auto pt = s.second;
  int turn;
  if (accumulate(begin(v), end(v), 0) % 2 == 0) {
    turn = 0;
  } else {
    turn = 1;
  }

  winner[s] = 1-turn;
  
  for (int i = 0; i < 6 && winner[s] == 1-turn; i++) {
    if (v[i] == 4) continue;

    pt += i+1;
    v[i]++;
    
    if (pt <= 31 && f(make_pair(v, pt)) == turn) {
      winner[s] = turn;
    }
    
    pt -= i+1;
    v[i]--;
  }
  
  return winner[s];
}

void solve(string s)
{
  vector<int> v(6, 0);
  int pt = 0;
  for (int i = 0; i < s.length(); i++) {
    int val = s[i] - '0';
    v[val-1]++;
    pt += val;
  }
  cout << s << ' ' << (f(make_pair(v, pt)) ? "B" : "A") << endl;
}

int main()
{
  string s;
  while (getline(cin, s)) {
    solve(s);
  }

  return 0;
}
