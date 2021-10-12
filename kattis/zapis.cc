#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll memo[201][201];
int N;
string s;

const ll MOD = 100000;

ll mymod(ll x)
{
  if (x < MOD) return x;

  return x % MOD + MOD;
}


ll solve(int start, int end)
{
  if (memo[start][end] >= 0)
    return memo[start][end];

  if (start == end) {
    return memo[start][end] = 1;
  }
  if ((end - start) % 2) {
    return memo[start][end] = 0;
  }

  const string left = "([{", right = ")]}";

  ll ans = 0;
  for (int i = 0; i < 3; i++) {
    if (s[start] == '?' || s[start] == left[i]) {
      for (int j = start+1; j < end; j++) {
	if (s[j] == '?' || s[j] == right[i]) {
	  ll temp = solve(start+1, j) * solve(j+1, end);
	  temp = mymod(temp);
	  ans += temp;
	  ans = mymod(ans);
	}
      }
    }
  }

  return memo[start][end] = ans;
}

int main()
{
  cin >> N;
  cin >> s;

  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= N; j++) {
      memo[i][j] = -1;
    }
  }
  ll ans = solve(0, N);

  if (ans >= MOD) {
    cout << setw(5) << setfill('0') << ans % MOD << endl;
  } else {
    cout << ans << endl;
  }
  
  return 0;
}
