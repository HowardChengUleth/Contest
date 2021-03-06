//
// There are many solutions.  What I have here is perhaps an overkill,
// using suffix arrays on the string made up from the concatenation of
// each password (doubled) and its reverse (doubled).
//
// Another way is to compute the minimum rotation for each string and its
// reverse as a signature so it is easy to search (also in code library).
//
// You can also use string hashing to do this.

#include <bits/stdc++.h>

using namespace std;

// Suffix array: O(n)  and  O(n log n)
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

// O(n)
void build_sarray(string str, int sarray[]) {
  int n = str.length();
  if (n <= 1) { for (int i = 0; i < n; i++)  sarray[i] = i; return; }

  vi s(n+3, 0), SA(n+3);
  for (int i = 0; i < n; i++) s[i] = (int)str[i] - CHAR_MIN + 1;
  sarray_int(s, SA, n, 256);
  copy(SA.begin(), SA.begin()+n, sarray);
}

// O(n)
void compute_lcp(string str, int sarray[], int lcp[]) {
  int n = str.length(), h = 0;  vi rank(n);
  for (int i = 0; i < n; i++)   rank[sarray[i]] = i;
  
  for (int i = 0; i < n; i++) {
    int k = rank[i];
    if (k > 0) {
      int j = sarray[k-1];
      while (i + h < n && j + h < n && str[i+h] == str[j+h]) h++;
      lcp[k] = h;
    }
    if (h > 0) h--;
  }
  lcp[0] = 0;
}

struct Comp{
  const string &s; int m;
  Comp(const string &str,int M) : s(str),m(M) { }
  bool operator()(int i, const string& p) const { return s.compare(i,m,p,0,m) < 0; }
  bool operator()(const string& p, int i) const { return s.compare(i,m,p,0,m) > 0; }
};

pii find(const string &str, const int sarray[], const string &pattern) {
  pair<const int *, const int *> p = 
    equal_range(sarray, sarray+str.size(), pattern, Comp(str,pattern.size()));
  return pii(p.first - sarray, p.second - sarray);
}

const int MAX_N = 1000000;
int N;
string pw[MAX_N];
pii bounds[MAX_N];
int sarray[6*MAX_N];
int pw_len[6*MAX_N];
  

int main()
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> pw[i];
  }

  string dict;
  dict.reserve(6*MAX_N);

  for (int i = 0; i < N; i++) {
    bounds[i].first = dict.length();
    string doublet = pw[i]+pw[i];
    dict += doublet + "#";
    reverse(begin(doublet), end(doublet));
    dict += doublet + '#';
    bounds[i].second = dict.length();
    fill(pw_len + bounds[i].first, pw_len + bounds[i].second, pw[i].length());
  }

  build_sarray(dict, sarray);

  for (int i = 0; i < N; i++) {
    auto res = find(dict, sarray, pw[i]);
    for (int j = res.first; j < res.second; j++) {
      if (!(bounds[i].first <= sarray[j] && sarray[j] < bounds[i].second) &&
	  pw[i].length() == pw_len[sarray[j]]) {
	cout << "Yes" << endl;
	return 0;
      }
    }
  }

  cout << "No" << endl;
  
  return 0;
}
