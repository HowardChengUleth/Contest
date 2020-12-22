#include <bits/stdc++.h>

using namespace std;

deque<int> P[2];

void read_deck(deque<int> &P)
{
  string line;
  getline(cin, line);
  while (getline(cin, line) && line != "") {
    P.push_back(stoi(line));
  }
}

void solveA()
{
  deque<int> Q[2] = { P[0], P[1] };
  
  while (!Q[0].empty() && !Q[1].empty()) {
    int c[2];
    for (int i = 0; i < 2; i++) {
      c[i] = Q[i].front();
      Q[i].pop_front();
    }
    if (c[0] > c[1]) {
      Q[0].push_back(c[0]);
      Q[0].push_back(c[1]);
    } else {
      Q[1].push_back(c[1]);
      Q[1].push_back(c[0]);
    }
  }

  int win = (Q[0].empty() ? 1 : 0);

  long long ans = 0;
  int i = 1;
  while (!Q[win].empty()) {
    ans += (i++) * Q[win].back();
    Q[win].pop_back();
  }
  cout << "A = " << ans << endl;
}

vector<int> get_config(deque<int> Q[2])
{
  vector<int> v(Q[0].size() + Q[1].size() + 1);
  for (auto x : Q[0]) {
    v.push_back(x);
  }
  v.push_back(-1);
  for (auto x : Q[1]) {
    v.push_back(x);
  }
  
  return v;
}

int solveB(deque<int> deck1, deque<int> deck2, bool top = true)
{
  set<vector<int>> seen;
  deque<int> Q[2] = { deck1, deck2 };

  int winner;
  while (true) {
    auto config = get_config(Q);

    // rule 1
    if (seen.count(config)) {
      winner = 0;
      break;
    }

    seen.insert(config);
    
    int c[2];
    for (int i = 0; i < 2; i++) {
      c[i] = Q[i].front();
      Q[i].pop_front();
    }

    if (c[0] <= Q[0].size() && c[1] <= Q[1].size()) {
      deque<int> d1, d2;
      for (int i = 0; i < c[0]; i++) {
	d1.push_back(Q[0][i]);
      }
      for (int i = 0; i < c[1]; i++) {
	d2.push_back(Q[1][i]);
      }
      winner = solveB(d1, d2, false);
    } else {
      winner = (c[0] > c[1]) ? 0 : 1;
    }
    int loser = 1-winner;

    Q[winner].push_back(c[winner]);
    Q[winner].push_back(c[loser]);

    if (Q[loser].empty()) {
      break;
    }
  }

  if (top) {
    long long ans = 0;
    int i = 1;
    while (!Q[winner].empty()) {
      ans += (i++) * Q[winner].back();
      Q[winner].pop_back();
    }
    cout << "B = " << ans << endl;
  }
  return winner;
}

int main()
{
  for (int i = 0; i < 2; i++) {
    read_deck(P[i]);
  }

  solveA();
  solveB(P[0], P[1]);
  
  return 0;
}
