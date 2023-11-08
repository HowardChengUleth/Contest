#include <bits/stdc++.h>

using namespace std;


int card_value(char ch)
{
  if (ch == 'A') return 0;
  if (isdigit(ch)) return min(7, ch - '0' - 1);
  return 7;
}

struct State
{
  bool up[7];
  int total[8];
  int pile[7];

  State()
  {
    fill(up, up+7, false);
    fill(total, total+7, 4);
    total[7] = 24;
  }

  State(string input)
  {
    for (int i = 0; i < 7; i++) {
      pile[i] = card_value(input[i]);
    }
    fill(up, up+7, false);
    fill(total, total+7, 4);
    total[7] = 24;
    for (int i = 0; i < 7; i++) {
      total[pile[i]]--;
    }
  }

  int key() const
  {
    int val = 0;
    for (int i = 0; i < 7; i++) {
      val *= 2;
      if (up[i]) val++;
    }
    for (int i = 0; i < 7; i++) {
      val *= 2;
      val += (total[i] ? 1 : 0);
    }
    val *= 52;
    val += total[7];
    return val;
  }

  bool operator<(const State &s) const
  {
    return key() < s.key();
  }

  int cardsleft() const
  {
    return accumulate(total, total+8, 0);
  }
  
  bool end() const
  {
    return (count(up, up+7, false) == 0);
  }

  void fixup()
  {
    for (int i = 0; i < 7; i++) {
      if (up[i]) {
	total[7] += total[i];
	total[i] = 0;
      }
    }
  }
  
  void flip(int card)
  {
    total[card]--;
    while (true) {
      if (card >= 7) break;
      if (up[card]) break;
      up[card] = true;
      card = pile[card];
    }
    fixup();
  }
};

map<State, double> memo;

double f(State s)
{
  if (memo.find(s) != memo.end()) {
    return memo[s];
  }

  double &ans = memo[s];
  ans = 0.0;

  if (s.end()) {
    return ans;
  }

  // now try picking each card
  ans = 1;
  for (int i = 0; i < 8; i++) {
    if (s.total[i] == 0) continue;
    State next = s;
    next.flip(i);
    ans += (double)s.total[i] / s.cardsleft() * f(next);
  }

  return ans;
}

int main()
{
  string input;
  cin >> input;

  State start(input);
 
  cout << fixed << setprecision(14) << f(start) << endl;

  return 0;
}
