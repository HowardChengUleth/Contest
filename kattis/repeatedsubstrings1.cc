#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD1 = 1000000007;
const ll MOD2 = 1000000009;
const int MAX_N = 100000;

ll pshash1[MAX_N];
ll inv1[MAX_N];
ll pshash2[MAX_N];
ll inv2[MAX_N];

void compute_hash(const string &s)
{
  ll b1 = 1, b2 = 1;
  ll prev1 = 0, prev2 = 0;
  for (int i = 0; i < s.length(); i++) {
    int val = s[i] - 'a';
    pshash1[i] = ((val * b1) % MOD1 + prev1) % MOD1;
    b1 = (b1 * 26) % MOD1;
    prev1 = pshash1[i];
    pshash2[i] = ((val * b2) % MOD2 + prev2) % MOD2;
    b2 = (b2 * 26) % MOD2;
    prev2 = pshash2[i];
  }
}

bool repeat(const string &s, int len, string &ans)
{
  int n = s.length();
  set<pair<ll,ll>> hash;

  bool ret = false;
  ans = string(n, 'z');
  for (int i = 0; i+len <= n; i++) {
    ll val1 = pshash1[i+len-1];
    if (i > 0) {
      val1 += MOD1 - pshash1[i-1];
      val1 %= MOD1;
    }
    val1 = (val1 * inv1[i]) % MOD1;
    ll val2 = pshash2[i+len-1];
    if (i > 0) {
      val2 += MOD2 - pshash2[i-1];
      val2 %= MOD2;
    }
    val2 = (val2 * inv2[i]) % MOD2;
    
    if (hash.count(make_pair(val1,val2)) > 0) {
      ans = min(ans, s.substr(i, len));
      ret = true;
    }
    hash.insert(make_pair(val1,val2));
  }
  return ret;
}

int main(void)
{
  string str;

  cin >> str;
  int n = str.length();
  
  inv1[0] = inv2[0] = 1;
  for (int i = 1; i < n; i++) {
    inv1[i] = (inv1[i-1] * 576923081) % MOD1;
    inv2[i] = (inv2[i-1] * 807692315) % MOD2;
  }
  compute_hash(str);

  string ans;
  int lo = 0, hi = n;      // lo = yes, hi = no
  while (hi - lo > 1) {
    int mid = (lo + hi)/2;
    if (repeat(str, mid, ans)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  repeat(str, lo, ans);
  cout << ans << endl;
  
  return 0;
}
