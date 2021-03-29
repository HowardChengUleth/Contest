#include <bits/stdc++.h>
using namespace std;

#define debug(a) cerr << #a << " = " << (a) << endl;
#define fst first
#define snd second
#define sz(x) (int)(x).size()
#define mp(x, y) make_pair(x, y)
#define all(X) begin(X), end(X)
#define rall(X) rbegin(X), rend(X)

template<typename T, typename U> ostream& operator<<(ostream& o, const pair<T, U>& x) { o << "(" << x.fst << ", " << x.snd << ")"; return o; }
template<typename T> ostream& operator<<(ostream& o, const vector<T>& x) { o << "["; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "]"; return o; }
template<typename T> ostream& operator<<(ostream& o, const set<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T> ostream& operator<<(ostream& o, const multiset<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T> ostream& operator<<(ostream& o, const unordered_set<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T> ostream& operator<<(ostream& o, const unordered_multiset<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const map<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const multimap<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const unordered_map<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const unordered_multimap<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
double time() { return double(clock()) / CLOCKS_PER_SEC; }

typedef long long ll;
const ll inf = 1ll << 60;
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, v, m;
  cin >> n >> v >> m;
  vector<vector<ll>> A(v, vector<ll>(v, inf));
  for (int i = 0, a, b, c; i < m; i++) {
    cin >> a >> b >> c;
    A[a][b] = min(ll(c), A[a][b]);
    A[b][a] = min(ll(c), A[b][a]);
  }

  for (int i = 0; i < v; i++)
    A[i][i] = 0;

  for (int k = 0; k < v; k++)
    for (int i = 0; i < v; i++)
      for (int j = 0; j < v; j++)
        A[i][j] = min(inf, min(A[i][j], A[i][k] + A[k][j]));

  for (int i = 0; i < v; i++)
    for (int j = 0; j < v; j++)
      assert(A[i][j] < inf);

  ll ans = inf;
  vector<int> P(n, 0); iota(all(P), 0);
  do {
    ll s = 0;
    for (int i = 0; i < n; i++)
      s += A[P[i]][P[(i+1) % n]];
    ans = min(ans, s);
  } while(next_permutation(begin(P)+1, end(P)));

  cout << ans << endl;
}

