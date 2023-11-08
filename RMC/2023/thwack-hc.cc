#include <bits/stdc++.h>

using namespace std;

map<string, int> memo;
typedef pair<int,string> pis;
typedef pair<int,int> pii;
typedef pair<string,string> pss;

int mex(const set<int> &nimval)
{
  int ans = 0;
  while (nimval.count(ans))
    ans++;
  return ans;
}

pss move_left(const string &s, int i)
{
  string left = s.substr(0, i-1) + s[i];
  string right = s.substr(i+1);
  return pss(left, right);
}

pss move_right(const string &s, int i)
{
  string left = s.substr(0, i);
  string right = s.substr(i+1);
  right[0] = s[i];
  return pss(left, right);
}

int solve(const string &s)
{
  int n = s.length();
  if (n <= 1) return 0;

  if (memo.find(s) != memo.end()) {
    return memo[s];
  }
  int &ans = memo[s];

  // no move, losing
  int B = count(begin(s), end(s), 'B');
  if (B == 0 || B == n) {
    return ans = 0;
  }

  set<int> nimval;
  
  for (int i = 0; i < n-1; i++) {
    if (s[i] == s[i+1]) continue;

    // try the left move
    auto [left, right] = move_left(s, i+1);
    nimval.insert(solve(left) ^ solve(right));

    // try the right move
    tie(left, right) = move_right(s, i);
    nimval.insert(solve(left) ^ solve(right));
  }

  return ans = mex(nimval);
}

int main()
{
  int N;
  string game;

  cin >> N >> game;

  vector<pis> chunks;

  int i, j;
  for (i = 0; i < N; i = j) {
    if (game[i] == '.') {
      j = i+1;
      continue;
    }
    for (j = i+1; j < N && game[j] != '.'; j++) 
      ;
    chunks.emplace_back(i, game.substr(i, j-i));
  }

  int nimber = 0;
  for (auto [i, s] : chunks) {
    nimber ^= solve(s);  
  }

  // there are no moves, works even if there are no chunks
  if (nimber == 0) {
    cout << 0 << endl;
    return 0;
  }

  set<pii> moves;
  for (auto [i, s] : chunks) {
    int temp_nimber = nimber ^ solve(s);
    for (int j = 0; j < s.length()-1; j++) {
      if (s[j] == s[j+1]) continue;
      auto [left, right] = move_left(s, j+1);
      if ((temp_nimber ^ solve(left) ^ solve(right)) == 0) {
	moves.emplace(i+j+1, i+j);
      }

      tie(left, right) = move_right(s, j);
      if ((temp_nimber ^ solve(left) ^ solve(right)) == 0) {
	moves.emplace(i+j, i+j+1);
      }
    }
  }

  cout << moves.size() << endl;
  for (auto [a, d] : moves) {
    cout << a+1 << ' ' << d+1 << endl;
  }
  
  return 0;
}
