#include <bits/stdc++.h>

using namespace std;

typedef int64_t ll;

const ll MOD = 1'000'000'000 + 7;

struct ModInt {
  ll x;
  ModInt(ll x = 0) : x(x + (x < 0) * MOD - (x >= MOD) * MOD) {}
  ModInt operator+(ModInt o) { return x + o.x; }
  ModInt operator-(ModInt o) { return x - o.x; }
  ModInt operator*(ModInt o) { return 1LL * x * o.x % MOD; }
  ModInt operator/(ModInt b) { return *this * b.inv(); }
  ModInt inv() { return pow(MOD - 2); }
  ModInt pow(long long e) {
    if (!e) return ModInt(1);
    ModInt r = pow(e / 2); r = r * r;
    return e % 2 ? *this * r : r;
  }
  bool operator==(ModInt o) { return x == o.x; }
};

ostream &operator<<(ostream &os, ModInt x)
{
  return os << x.x;
}

vector<ModInt> BerlekampMassey(vector<ModInt> s) {
  int n = s.size();
  vector<ModInt> C(n), B(n);
  C[0] = B[0] = 1;

  auto b = C[0]; int L = 0;
  for (int i = 0, m = 1; i < n; ++i) {
    /// Calculate discrepancy
    auto d = s[i];
    for (int j = 1; j <= L; ++j)
      d = d + C[j] * s[i - j];
    if (d == 0) { ++m; continue; }
    /// C -= d / b * B * X^m
    auto T = C; auto coef = d / b;
    for (int j = m; j < n; ++j)
      C[j] = C[j] - coef * B[j - m];
    if (2 * L > i) { ++m; continue; }
    L = i + 1 - L; B = T; b = d; m = 1;
  }
  C.resize(L + 1); C.erase(C.begin());
  for (auto& x : C) x = x * (-1);
  return C;
}

using Poly = vector<ModInt>;

// M[i] = list of (j, M[i][j])
typedef vector<vector<pair<int,ModInt>>> Matrix;

Poly LinearRec(Poly trans, ll k) {
  int n = trans.size(); // assert(n <= (int)first.size());
  if (!n) return {0};
  Poly r(n + 1), b(r); r[0] = b[1] = 1;
  //  auto ans = b[0];

  auto combine = [&](Poly a, Poly b) { // a * b mod trans
    Poly res(n * 2 + 1);
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= n; ++j)
        res[i + j] = res[i + j] + a[i] * b[j];
    for (int i = 2 * n; i > n; --i)
      for (int j = 0; j < n; ++j)
        res[i - 1 - j] = res[i - 1 - j] + res[i] * trans[j];
    res.resize(n + 1);
    return res;
  };
  // Consider caching the powers for multiple queries
  for (++k; k; k /= 2) {
    if (k % 2) r = combine(r, b);
    b = combine(b, b);
  }
  return r;
}

vector<ModInt> Power(Matrix M, ll k, vector<ModInt> v) {
  int n = M.size();
  vector<Poly> first(2 * n, Poly(n));
  first[0] = v;
  vector<ModInt> s(2 * n);

  Poly w(n);
  mt19937 wgen;
  for (int i=0;i<n;++i) {
    w[i] = wgen() % MOD;
    s[0] = s[0] + v[i] * w[i];
  }
  
  // Step 1 (optimizable to O(m * n))
  for (int i = 1; i < 2 * n; ++i) {
    for (int j = 0; j < n; ++j)
      for (auto [k, coeff] : M[j]) {
	first[i][k] = first[i][k] + coeff * first[i-1][j];
      }
      
    for(int j=0;j<n;++j) s[i] = s[i] + first[i][j] * w[j];
  }

  // Step 2 (O(n^2))
  auto trans = BerlekampMassey(s);
  int rec = trans.size();

  // Step 3 (O(n^2 log k))
  Poly c = LinearRec(trans, k);

  // Step 4 (O(n^2))
  vector<ModInt> ans(n);
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < rec; ++j)
      ans[i] = ans[i] + c[j + 1] * first[j][i];

  return ans;
}



ll n;
int p, s, c;

struct Problem
{
  char g;
  ll t;
  int s, c, b;

  void read()
  {
    cin >> t >> g >> s >> c >> b;
  }

  bool can_solve(int sA, int cA) const
  {
    if (g == 'B') {
      sA = ::s - sA;
      cA = ::c - cA;
    }

    return sA >= s && cA >= c && sA+cA >= b;
  }
};

typedef pair<int,int> pii;

Problem prob[11];
int teamA2index(int solver, int coder)
{
  return solver * 36 + coder;
}

pii index2teamA(int index)
{
  return pii(index / 36, index % 36);
}

const int DIM = 36*36;

// transition matrix
//
// M[i,j] = number of ways to go from configuration j to configuration i
Matrix M;

void computeM()
{
  M.resize(DIM);
	   
  for (int sA = 0; sA <= s; sA++) {
    for (int cA = 0; cA <= c; cA++) {
      // 0 = no change, -1 = A->B, +1 = B->A
      // A->B
      for (int ds = -1; ds <= 1; ds++) {
	for (int dc = -1; dc <= 1; dc++) {
	  int sA2 = sA + ds;
	  int cA2 = cA + dc;

	  // out of bounds
	  if (!(0 <= sA2 && sA2 <= s && 0 <= cA2 && cA2 <= c))
	    continue;

	  int j = teamA2index(sA, cA);
	  int i = teamA2index(sA2, cA2);
	  int ways_s, ways_c;

	  if (ds == -1) {
	    ways_s = sA;
	  } else if (ds == 0) {
	    ways_s = 1;
	  } else {
	    ways_s = s-sA;
	  }
	  if (dc == -1) {
	    ways_c = cA;
	  } else if (dc == 0) {
	    ways_c = 1;
	  } else {
	    ways_c = c-cA;
	  }
	  
	  M[i].emplace_back(j, (ways_s * ways_c) % MOD);
	}
      }
    }
  }
}

// C = A * B
void mult(ll A[DIM][DIM], ll B[DIM][DIM], ll C[DIM][DIM])
{
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      C[i][j] = 0;
      for (int k = 0; k < DIM; k++) {
	C[i][j] = (C[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
      }
    }
  }
}

// w = A * v
void mult(ll A[DIM][DIM], ll v[DIM], ll w[DIM])
{
  for (int i = 0; i < DIM; i++) {
    w[i] = 0;
    for (int j = 0; j < DIM; j++) {
      w[i] = (w[i] + (A[i][j] * v[j]) % MOD) % MOD;
    }
  }
}

ll tempB[DIM][DIM];

// C = A^n
void exp(ll A[DIM][DIM], ll n, ll C[DIM][DIM])
{
  if (n == 0) {
    for (int i = 0; i < DIM; i++) {
      for (int j = 0; j < DIM; j++) {
	C[i][j] = (i == j);
      }
    }
    return;
  }

  if (n % 2) {
    exp(A, n-1, tempB);
    mult(A, tempB, C);
  } else {
    exp(A, n/2, tempB);
    mult(tempB, tempB, C);
  }
}



int main()
{
  cin >> n >> p >> s >> c;
  for (int i = 0; i < p; i++) {
    prob[i].read();
    --prob[i].t;
  }

  // insert 1 artificial problem at the end
  prob[p].g = 'A';
  prob[p].t = n-1;
  prob[p].s = s;
  prob[p].c = c;
  prob[p].b = s+c;
  p++;

  computeM();

  vector<ModInt> ways(DIM, 0);
  ways[teamA2index(s, c)] = 1;

  ll last = 0;
  for (int i = 0; i < p; i++) {
    ll next = prob[i].t;
    assert(last <= next);
    
    ll steps = next - last;
    ways = Power(M, steps, ways);

    for (int sA = 0; sA <= s; sA++) {
      for (int cA = 0; cA <= c; cA++) {
	if (!prob[i].can_solve(sA, cA)) {
	  ways[teamA2index(sA, cA)] = 0;
	}
      }
    }

    last = next;
  }

  cout << ways[teamA2index(s, c)] << endl;
  
  return 0;
}
