#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

const ll p = 100000007;

ll N, K, B, R;
pll blocked[500];
ll maxM;


ll gcd(ll a, ll b, ll &s, ll &t) { // a*s+b*t = g
  if (b==0) { t = 0; s = (a < 0) ? -1 : 1; return (a < 0) ? -a : a;
  } else { ll g = gcd(b, a%b, t, s);  t -= a/b*s;  return g; }
}

long long fast_exp_mod(long long b, long long n, long long m) {
  if (n == 0) return 1 % m;
  if (n % 2 == 0) return fast_exp_mod((b*b)%m, n/2, m);
  return (fast_exp_mod(b, n-1, m) * b) % m;
}

ll discrete_log(ll p,ll b,ll n){
  map<ll,ll> M; ll jump = ceil(sqrt(p));
  for(int i=0;i<jump && i<p;i++) M[fast_exp_mod(b,i,p)] = i+1;
  for(int i=0;i<p-1;i+=jump){
    ll x = (n*fast_exp_mod(b,p-i-1,p)) % p;
    if(M.find(x) != M.end()) return (i+M[x]-1) % (p-1);
  }
  return -1;
}

// return the number of ways to fill a column, assuming that we want to
// colour from row prev+1 to row curr-1
ll count_col(ll prev, ll curr)
{
  ll ways = 1;
  ll num = curr - prev - 1;
  if (num > 0) {
    // first one can be any of the K colours
    ways = ways * K % p;

    // the rest only has K-1 choices
    ways = ways * fast_exp_mod(K-1, num-1, p) % p; 
  }
  return ways;
}

ll count_ways()
{
  ll ways = 1;
  ll last_col = 0, last_row = 0;
  ll num;

  int i = 0;
  while (i < B) {
    ll col = blocked[i].first, row = blocked[i].second;
    if (col != last_col) {
      // finish off the previous col
      if (last_col) {
	ways = ways * count_col(last_row, maxM+1) % p;
      }

      // deal with the missing cols
      num = col - last_col - 1;
      ways = ways * fast_exp_mod(count_col(0, maxM+1), num, p) % p;

      // from top of current col to current row
      ways = ways * count_col(0, row) % p;
    } else {
      ways = ways * count_col(last_row, row) % p;
    }
    last_col = col;
    last_row = row;
    i++;
  }
  
  // finish off the previous col and remaining cols
  if (last_col) {
    ways = ways * count_col(last_row, maxM+1) % p;
    num = N - last_col;
    if (num > 0) {
      ways = ways * fast_exp_mod(count_col(0, maxM+1), num, p) % p;
    }
  }

  return ways;
}

// look at first unoccupied row (maxM+1)
ll count_first_empty_row()
{
  // number of blocked cells in the previous row
  int count = 0;
  for (int i = 0; i < B; i++) {
    if (blocked[i].second == maxM) count++;
  }
  if (B == 0) {
    count = N;
  }

  // if there is something on top, we can choose any of the K colours
  // otherwise we can only choose K-1 colours.
  return fast_exp_mod(K, count, p) * fast_exp_mod(K-1, N-count, p) % p;
}
  
ll solve()
{
  cin >> N >> K >> B >> R;

  maxM = 0;
  for (int i = 0; i < B; i++) {
    cin >> blocked[i].second >> blocked[i].first;  // column, row!
    maxM = max(blocked[i].second, maxM);
  }

  // let's figure out the number of ways to colour the top maxM+1 rows
  sort(blocked, blocked+B);

  ll ways = count_ways();

  // already done
  if (maxM > 0 && ways == R) {
    return maxM;
  }

  // just one more row
  ways = ways * count_first_empty_row() % p;
  maxM++;
  if (ways == R) {
    return maxM;
  }

  // the rest: each row is (K-1)^(N) for m extra rows
  //
  // so R = ways * ((K-1)^N)^m mod p
 
  // invert ways and multiply by R
  ll s, t;
  gcd(ways, p, s, t);
  if (s < 0) s += p;
  ll lhs = R * s % p;

  // now we have:
  //
  // lhs = ((K-1)^N)^m mod p
  //
  // or lhs = b^m mod p   with b = (K-1)^N
  // 
  // so m = discrete log of lhs to the base b, mod p
  ll b = fast_exp_mod(K-1, N, p);
  ll m = discrete_log(p, b, lhs);

  return m + maxM;      // the m are extra rows in addition to maxM
}

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": " << solve() << endl;
  }
  return 0;
}
