#include <bits/stdc++.h>

using namespace std;

typedef pair<char, char> pcc;
map<pcc, char> rule;

typedef long long ll;

map<char,int> ch_index;
int get_index(char c)
{
  if (ch_index.find(c) == ch_index.end()) {
    int s = ch_index.size();
    ch_index[c] = s;
  }
  return ch_index[c];
}

int num_char;

int get_index(char c1, char c2) {
  int i1 = get_index(c1);
  int i2 = get_index(c2);
  return i1 * num_char + i2;
}

vector<ll> apply(const vector<ll> &v)
{
  vector<ll> w(v.size(), 0);

  for (auto [c1, i] : ch_index) {
    if (c1 == '$') continue;
    int t = get_index('$',c1);
    w[t] += v[t];
    t = get_index(c1, '$');
    w[t] += v[t];
  }
  
  for (auto [p, to] : rule) {
    char c1 = p.first;
    char c2 = p.second;

    int loc;
    loc = get_index(c1, to);
    w[loc] += v[get_index(c1, c2)];
    
    loc = get_index(to, c2);
    w[loc] += v[get_index(c1, c2)];
  }

  return w;
}



int main()
{
  string s, blank;

  getline(cin, s);
  getline(cin, blank);

  s = "$" + s + "$";
  get_index('$');
  for (auto c : s) {
    get_index(c);
  }
  
  string from, arrow;
  char to;
  while (cin >> from >> arrow >> to) {
    get_index(from[0]);
    get_index(from[1]);
    get_index(to);
    pcc p(from[0], from[1]);
    rule[p] = to;
  }
  num_char = ch_index.size();
  
  vector<ll> v(num_char*num_char, 0);
  for (int i = 0; i < s.length()-1; i++) {
    int t = get_index(s[i], s[i+1]);
    v[t]++;
  }
  
  for (int i = 0; i < 40; i++) {
    v = apply(v);
  }

  ll freq[256] = {0};
  for (auto [c1, i] : ch_index) {
    for (auto [c2, j] : ch_index) {
      int t = get_index(c1, c2);
      int mult = (c1 == '$' || c2 == '$') ? 2 : 1;
      freq[c1] += v[t]*mult;
      freq[c2] += v[t]*mult;
    }
  }

  ll maxf = 0, minf = LLONG_MAX;
  for (int i = 0; i < 256; i++) {
    if (freq[i] && i != '$') {
      freq[i] /= 2;
      maxf = max(maxf, freq[i]);
      minf = min(minf, freq[i]);
    }
  }
  cout << maxf - minf << endl;

  return 0;
}
