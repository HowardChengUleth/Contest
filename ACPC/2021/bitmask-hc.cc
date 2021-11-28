#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 12;

int n;
string bdata;
int C[MAX_N+1];

// I'm intentionally not trying to be very clever here.  The goal here is
// a relatively straightforward brute force search.
int solve(int idx, map<string,int> &S)
{
  if (idx >= n)
    return 0;

  int ans = INT_MAX;
  for (int e = idx+1; e <= n; e++) {
    int length = e - idx;
    string mask = bdata.substr(idx, length);

    S[mask]++;
    int t = solve(e, S);
    S[mask]--;
    if (S[mask] == 0) {
      t += C[length];
    }
    ans = min(ans, t);
  }

  return ans;
}

int main()
{
  cin >> bdata;
  n = bdata.length();

  for (int i = 0; i < n; i++) {
    cin >> C[i+1];
  }

  map<string,int> S;
  cout << solve(0, S) << endl;

  return 0;
}
