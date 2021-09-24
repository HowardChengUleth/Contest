//
// There are 3 types of inversions
//
// 1. inversions of existing 0 and 1:
//    - for each 0, the number of inversions involved with that 0 is the
//      number of 1s to its left
//    - for each 1, the number of inversions involved with that 1 is the
//      number of 0s to its right
//
//    But if count both then we will double count.  So we only do the first
//    one.
//
//    All of this have to be multiplied by 2^Q if Q is the number of ?s
//
// 2. inversions of ? and an existing 0 or 1
//    - we can try both 0 and 1 for ?, and then we apply the two cases above
//      But this will be repeated 2^(Q-1) times if there are Q ?s
//    - we do have to try both this time because there is no double counting
//
// 3. inversions of ? and ?
//    - we can only get inversion if we assign 1 to the first ? and 0 to the
//      second ?
//    - to avoid double counting, we assume each ? can be a 0 and see how many
//      ? to its left can be set to 1s.
//
//      Basically, if there are L ? to its left, then the number of inversions
//      that can be introduced is
//
//         sum_{k=0}^L  C(L,k) * k
//
//      But if there are R ? to its right, then each of these will be repeated
//      2^R times.
//
//    - using the fact that f(x) = (1+x)^L = sum_{k=0}^L C(L,k) x^k, we
//      see that f'(1) = L*2^(L-1) = sum_{k=0}^L C(L,k)*k
//
//    - so finally it is L * 2^(L-1) * 2^R
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

string s;
int n;

// number of 1s and ?s to its left, number of 0s and ?s to its right
int left1[500000], leftq[500000], right0[500000], rightq[500000];

ll expmod(ll b, int n)
{
  if (!n) return 1;
  if (n % 2 == 0) {
    return expmod((b*b)%MOD, n/2);
  }
  return (b * expmod(b, n-1)) % MOD;
}

int main()
{
  cin >> s;
  n = s.length();

  left1[0] = leftq[0] = 0;
  for (int i = 1; i < n; i++) {
    left1[i] = left1[i-1] + (s[i-1] == '1');
    leftq[i] = leftq[i-1] + (s[i-1] == '?');
  }
  right0[n-1] = 0;
  rightq[n-1] = 0;
  for (int i = n-2; i >= 0; i--) {
    right0[i] = right0[i+1] + (s[i+1] == '0');
    rightq[i] = rightq[i+1] + (s[i+1] == '?');
  }

  ll ans = 0;

  for (int i = 0; i < n; i++) {
    int L = leftq[i];
    int R = rightq[i];

    // type 1
    if (s[i] == '0') {
      ans += (left1[i] * expmod(2, L+R)) % MOD;
      ans %= MOD;
    }

    if (s[i] == '?') {
      // type 2
      ans += (left1[i] + right0[i]) * expmod(2, L+R) % MOD;
      ans %= MOD;

      // type 3
      if (L > 0) {
	ans += (expmod(2, L-1+R) * L) % MOD;
	ans %= MOD;
      }
    }
  }
  cout << ans << endl;
  

  return 0;
}
