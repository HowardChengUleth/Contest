#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define debug(a) cerr << #a << " = " << (a) << endl;
#define fst first
#define snd second
#define sz(x) (int)(x).size()
#define all(X) begin(X), end(X)

template<typename T, typename U> ostream& operator<<(ostream &o, const pair<T, U>& x) {
    o << "(" << x.fst << ", " << x.snd << ")"; return o;
}

template<typename T> ostream& operator<<(ostream &o, const vector<T>& x) {
    o << "["; int b = 0; for (auto &a: x) o << (b++ ? ", ": "" ) << a; o << "]"; return o;
}

template<typename T> ostream& operator<<(ostream &o, const set<T>& x) {
    o << "{"; int b = 0; for (auto &a: x) o << (b++ ? ", ": "" ) << a; o << "}"; return o;
}

template<typename T, typename U> ostream& operator<<(ostream &o, const map<T, U>& x) {
    o << "{"; int b = 0; for (auto &a: x) o << (b++ ? ", ": "" ) << a; o << "}"; return o;
}

typedef long long ll;

ll P = 1000000007;

long long H(long long previousHash, string &transaction,
            long long token) {
  long long v = previousHash;
  for (int i = 0; i < transaction.length(); i++) {
    v = (v * 31 + transaction[i]) % 1000000007;
  }
  return (v * 7 + token) % 1000000007;
}

ll t(ll v, string transaction) {
    for (int i = 0; i < transaction.length(); i++) {
        v = (v * 31 + transaction[i]) % 1000000007;
    }
    // ll u = (v*31 + (int)'a') % P;
    ll u = v;
    u *= 7;
    u %= P;
    ll token = P - (u % 10000000);
    assert(((u + token) % P) % 10000000 == 0);
    while (token >= 1000000000) {
      token = (token + 10000000) % P;
    }
    return token;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll v;
    cin >> v;
    int i = 0;
    string a = "a";
    ll tok1 = t(v, a);
    ll u = H(v, a, tok1);

    string b = a;
    ll tok2 = t(u, b);
    ll u_ = H(u, b, tok2);
    cout << a << ' ' << tok1 << endl;
    cout << b << ' ' << tok2 << endl;
}
