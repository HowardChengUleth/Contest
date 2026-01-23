#include <bits/stdc++.h>

using namespace std;

// if you can swap misplaced 0 and 1 to make it work, always do it
// (there is never a reason to swap two characters that are the same)
bool swap01(string &S, const string &T)
{
  int pos0 = -1;
  int pos1 = -1;
  for (int i = 0; i < S.length(); i++) {
    if (S[i] == '0' && T[i] == '1') {
      pos0 = i;
    }
    if (S[i] == '1' && T[i] == '0') {
      pos1 = i;
    }
  }

  if (pos0 >= 0 && pos1 >= 0) {
    swap(S[pos0], S[pos1]);
    return true;
  }

  return false;
}

int do_swaps(string &S, const string &T)
{
  int count = 0;
  while (swap01(S, T)) {
    count++;
  }
  return count;
}

int findreplace(string &S, const string &T, char from, char to, int max_change)
{
  int count = 0;
  
  // change the ones that are in the right place
  for (int i = 0; i < S.length() && max_change > 0; i++) {
    if (S[i] == from && T[i] == to) {
      S[i] = to;
      max_change--;
      count++;
    }
  }

  // replace the ones that are not in the right place anyway
  for (int i = 0; i < S.length() && max_change > 0; i++) {
    if (S[i] == from) {
      S[i] = to;
      max_change--;
      count++;
    }
  }

  return count;
}
void solve()
{
  string S, T;
  cin >> S >> T;

  int ans = 0;
  
  // do as many swaps
  ans += do_swaps(S, T);

  // let's count number of 0s and 1s in each of S and T
  int S0 = count(begin(S), end(S), '0');
  int S1 = count(begin(S), end(S), '1');
  int SQ = count(begin(S), end(S), '?');
  int T0 = count(begin(T), end(T), '0');
  int T1 = count(begin(T), end(T), '1');

  // If T0 > S0, we must turn some ? to 0
  findreplace(S, T, '?', '0', T0-S0);

  // turn the rest of ? to 1
  replace(begin(S), end(S), '?', '1');
  ans += SQ;

  S0 = count(begin(S), end(S), '0');
  S1 = count(begin(S), end(S), '1');

  // now turn 0's into 1s if needed
  ans += findreplace(S, T, '0', '1', T1-S1);

  // now swaps 0s and 1s if needed
  ans += do_swaps(S, T);

  if (S == T) {
    cout << ans << endl;
  } else {
    cout << -1 << endl;
  }
}

int main()
{
  int C;
  cin >> C;
  for (int i = 1; i <= C; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  return 0;
}
