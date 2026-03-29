// idea: this is a DP whose states are how many of each type of dice is left
// and how much health is left
//
// look for the first unused dice, and try rolling it in all possible ways
// and recurse.
#include <bits/stdc++.h>

using namespace std;

map<vector<int>,double> memo;
int sides[7] = {2, 4, 6, 8, 10, 12, 20};

double f(vector<int> &input)
{
  if (memo.find(input) != end(memo)) {
    return memo[input];
  }

  double &ans = memo[input];

  if (input[7] == 0) {
    // enemy is dead
    return ans = 1.0;
  }

  for (int i = 0; i < 7; i++) {
    if (input[i] == 0) continue;

    input[i]--;
    ans = 0.0;

    // roll this die
    for (int r = 1; r <= sides[i]; r++) {
      int old_total = input[7];
      int new_total = max(0, input[7] - r);
      input[7] = new_total;
      ans += 1.0/sides[i] * f(input);
      input[7] = old_total;
    }

    input[i]++;
    break;
  }

  return ans;
}

int main()
{
  vector<int> input(8);
  for (int i = 0; i < 8; i++) {
    cin >> input[i];
  }

  cout << fixed << setprecision(10) << f(input) << endl;
  
  return 0;
}
