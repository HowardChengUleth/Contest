#include <bits/stdc++.h>
using namespace std;

#define debug(a) cerr << #a << " = " << (a) << endl;
#define fst first
#define snd second
#define mp(x, y) make_pair(x, y)
#define sz(x) (int)(x).size()
#define all(X) begin(X), end(X)
#define rall(X) rbegin(X), rend(X)

template<typename T, typename U> ostream& operator<<(ostream& o, const pair<T, U>& x) { 
  o << "(" << x.fst << ", " << x.snd << ")"; return o;
}

template<typename T> ostream& operator<<(ostream& o, const vector<T>& x) {
  o << "["; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "]"; return o;
}

template<typename T> ostream& operator<<(ostream& o, const set<T>& x) {
  o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o;
}

template<typename T, typename U> ostream& operator<<(ostream& o, const map<T, U>& x) {
  o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o;
}




const int INF = 50000*10000*2;
struct Matrix
{
  const int n = 5;
  int A[5][5];

  Matrix()
  {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	A[i][j] = INF;
      }
    }
  }

  int operator()(int i, int j) const
  {
    return A[i][j];
  }

  int &operator()(int i, int j)
  {
    return A[i][j];
  }

  Matrix &operator=(const Matrix &B)
  {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	A[i][j] = B.A[i][j];
      }
    }
    return *this;
  }
};

ostream &operator<<(ostream &os, const Matrix &M)
{
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      os << setw(11) << M(i,j);
    }
    os << endl;
  }
  return os;
}

Matrix mult(Matrix A, Matrix B)
{
  Matrix C;
  for (int i = 0; i < C.n; i++) {
    for (int j = 0; j < C.n; j++) {
      for (int k = 0; k < C.n; k++) {
	C(i,j) = min(C(i,j), A(i,k) + B(k,j));
      }
    }
  }
  return C;
}

// found on codeforces blog
// short non-recursive implementation.
template<typename T>
struct segment {
  int n; T id; function<T(T, T)> op;
  vector<T> S;
  segment(int n, T id, function<T(T, T)> op, const vector<T>& A = {}) 
    : n(n), id(id), op(op), S(2*n, id) {
    for (int i = 0; i < sz(A); i++) S[n+i] = A[i];
    for (int i = n-1; i > 0; i--) S[i] = op(S[2*i], S[2*i+1]);
  }
  // add v to A[x] (can change to = for setting)
  void update(int x, T v) {
    for (S[x += n] += v; x > 1; x /= 2) 
      S[x/2] = op(S[x], S[x^1]);
  }
  // query range A[l], ... , A[r-1].
  T query(int l, int r) {
    T ansL = id, ansR = id;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) ansL = op(ansL, S[l++]);
      if (r & 1) ansR = op(S[--r], ansR);
    }
    return op(ansL, ansR);
  }
};

int K, N, M, O;

int main()
{
  cin >> K >> N >> M >> O;
  int levels = (N+(K-1))/K-1;
  vector<Matrix> A(levels);

  for (int i = 0; i < M; i++) {
    int a, b, t;
    cin >> a >> b >> t;

    int index = a / K;
    A[index](a%K, b%K) = t;
  }

  for (int i = 0; i < levels; i++) {
    //    debug(A[i]);
  }

  Matrix id;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      id(i,j) = (i == j) ? 0 : INF;
    }
  }
  segment<Matrix> st(levels, id, mult, A);

  for (int i = 0; i < O; i++) {
    int a, b;
    cin >> a >> b;

    int from = a/K;
    int to = b/K;

    //    cout << "query " << i+1 << ":" << endl;
    
    if (to <= from) {
      cout << "-1" << endl;
      continue;
    }
    /*
    debug(from);
    debug(to);
    */

    
    auto res = st.query(from, to);

    //    debug(res);
    
    int ans = res(a%K, b%K);
    if (ans < INF) {
      cout << ans << endl;
    } else {
      cout << "-1" << endl;
    }
  }
  /*
  auto res = st.query(0,1);
  cout << "0 - 1" << endl;
  debug(res);

  res = st.query(1,2);
  cout << "1 - 2" << endl;
  debug(res);

  res = st.query(2,3);
  cout << "2 - 3" << endl;
  debug(res);

  res = st.query(3,4);
  cout << "3 - 4" << endl;
  debug(res);

  res = st.query(0,2);
  cout << "0 - 2" << endl;
  debug(res);

  res = st.query(2,4);
  cout << "2 - 4" << endl;
  debug(res);

  res = st.query(0,3);
  cout << "0 - 3" << endl;
  debug(res);
  */
  
  return 0;
}
