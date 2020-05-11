#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tr1/tuple>
#include <stack>
#include <climits>

using namespace std;
using namespace std::tr1;

class MinQueue
{
private:
  stack<pair<int,int> > s1;
  stack<int> s2;
  int m1, m2;

  void move() {
    if (!s1.empty()) return;
    while (!s2.empty()) {
      s1.push(make_pair(s2.top(), m1));
      m1 = ::min(s2.top(), m1);
      s2.pop();
    }
    m2 = INT_MAX;         // min of empty queue
  }
  
public:
  // whatever the min of an empty queue should be
  MinQueue() : m1(INT_MAX), m2(INT_MAX) { }
  
  int min() const {
    return ::min(m1, m2);
  }

  bool empty() const {
    return s1.empty() && s2.empty();
  }
  
  void push(int x) {
    m2 = ::min(m2, x);
    s2.push(x);
  }

  int front() {
    move();
    return s1.top().first;
  }

  void pop() {              // doesn't check for empty queue
    move();
    m1 = s1.top().second;
    s1.pop();
  }
};

// Suffix array: O(n)
// NOTE: the empty suffix is not included in this list, so sarray[0] != n.
// lcp[i] contains the length of the longest common prefix of the suffixes
// pointed to by sarray[i-1] and sarray[i].  lcp[0] is defined to be 0.
typedef pair<int,int> pii;
typedef tuple<int,int,int> tiii;
typedef vector<int> vi;

void radixPass(vi &a, vi &b, vi &r, int n, int K, int off=0) {
  vi c(K+1, 0);
  for (int i = 0;  i < n;  i++) c[r[a[i]+off]]++;
  for (int i = 0, sum = 0;  i <= K;  i++) {
     int t = c[i];  c[i] = sum;  sum += t;
  }
  for (int i = 0;  i < n;  i++) b[c[r[a[i]+off]]++] = a[i];
}

#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
void sarray_int(vi &s, vi &SA, int n, int K) {
  int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2; 
  vi s12(n02 + 3, 0), SA12(n02 + 3, 0), s0(n0), SA0(n0);
 
  for (int i=0, j=0;  i < n+(n0-n1);  i++) if (i%3 != 0) s12[j++] = i;

  radixPass(s12 , SA12, s, n02, K, 2);
  radixPass(SA12, s12 , s, n02, K, 1);  
  radixPass(s12 , SA12, s, n02, K, 0);

  int name = 0, c0 = -1, c1 = -1, c2 = -1;
  for (int i = 0;  i < n02;  i++) {
    if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2) { 
      name++;  c0 = s[SA12[i]];  c1 = s[SA12[i]+1];  c2 = s[SA12[i]+2];
    }
    if (SA12[i] % 3 == 1) { s12[SA12[i]/3]      = name; }
    else                  { s12[SA12[i]/3 + n0] = name; }
  }

  if (name < n02) {
    sarray_int(s12, SA12, n02, name);
    for (int i = 0;  i < n02;  i++) s12[SA12[i]] = i + 1;
  } else
    for (int i = 0;  i < n02;  i++) SA12[s12[i] - 1] = i; 

  for (int i=0, j=0;  i < n02;  i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
  radixPass(s0, SA0, s, n0, K);

  for (int p=0,  t=n0-n1,  k=0;  k < n;  k++) {
    int i = GetI(), j = SA0[p];
    if (SA12[t] < n0 ? 
        (pii(s[i], s12[SA12[t] + n0]) < pii(s[j], s12[j/3])) :
	(tiii(s[i],s[i+1],s12[SA12[t]-n0+1]) < tiii(s[j],s[j+1],s12[j/3+n0]))) {
      SA[k] = i;  t++;
      if (t == n02) 
        for (k++;  p < n0;  p++, k++) SA[k] = SA0[p];
    } else { 
      SA[k] = j;  p++; 
      if (p == n0) 
        for (k++;  t < n02;  t++, k++) SA[k] = GetI(); 
    }  
  } 
}

void build_sarray(const string &str, int sarray[]) {
  int n = str.length();
  if (n <= 1) {
    for (int i = 0; i < n; i++)  sarray[i] = i;
    return;
  }

  vi s(n+3, 0), SA(n+3);
  for (int i = 0; i < n; i++)
    s[i] = (int)str[i] - CHAR_MIN + 1;
  sarray_int(s, SA, n, 256);
  copy(SA.begin(), SA.begin()+n, sarray);
}

void compute_lcp(const string &str, int sarray[], int lcp[]) {
  int n = str.length();
  vi rank(n);
  for (int i = 0; i < n; i++)   rank[sarray[i]] = i;

  int h = 0;
  for (int i = 0; i < n; i++) {
    int k = rank[i];
    if (k == 0) {
      lcp[k] = -1;
    } else {
      int j = sarray[k-1];
      while (i + h < n && j + h < n && str[i+h] == str[j+h]) h++;
      lcp[k] = h;
    }
    if (h > 0) h--;
  }
  lcp[0] = 0;
}

struct Comp
{
  const string &s;

  Comp(const string &str) : s(str) { }
  bool operator()(int i, const string &p) const {
    return s.substr(i, p.length()) < p;
  }
  bool operator()(const string &p, int i) const {
    return p < s.substr(i, p.length());
  }
};

pii find(const string &str, const int sarray[], const string &pattern) {
  int n = str.length();
  pair<const int *, const int *> p = 
    equal_range(sarray, sarray+n, pattern, Comp(str));
  return pii(p.first - sarray, p.second - sarray);
}

int sarray[6000010];
int lcp[6000010];
int pos[6];
int N;

int get_type(int k)
{
  for (int i = N-1; i >= 0; i--) {
    if (k >= pos[i]) return i;
  }
  return -1;
}

#include <iomanip>

void solve()
{
  cin >> N;

  string s;

  for (int i = 0; i < N; i++) {
    string g;
    cin >> g;
    pos[i] = s.length();
    s += g;
    s += ' ';
  }

  build_sarray(s, sarray);
  compute_lcp(s, sarray, lcp);

  int type[6] = {0};
  int num_type = 0;
  unsigned int start = 0, end = 0;
  MinQueue mq;
  int ans = INT_MIN;
  
  while (start < s.length() && end < s.length()) {
    if (s[sarray[start]] == ' ' && start < s.length()) {
      start++;  continue;
    }
    
    end = max(end, start);
    while (num_type != N && end < s.length()) {
      if (type[get_type(sarray[end])]++ == 0) num_type++;
      if (end > start) mq.push(lcp[end]);
      end++;
    }

    if (num_type == N) {
      ans = max(ans, mq.min());
    }
    
    if (--type[get_type(sarray[start])] == 0) num_type--;
    start++;
    mq.pop();
  }

  cout << ans << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();
    
  return 0;
}
