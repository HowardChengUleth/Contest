#include <bits/stdc++.h>

using namespace std;

struct Pizza
{
  string s;
  int m1, m2;
  string list1[20], list2[20];

  void read()
  {
    cin >> s;
    cin >> m1;
    for (int i = 0; i < m1; i++) {
      cin >> list1[i];
    }
    cin >> m2;
    for (int i = 0; i < m2; i++) {
      cin >> list2[i];
    }
  }

};

typedef pair<string,string> pss;

Pizza pizza[60];
int n;

bool check(const string &s1, string &s2)
{
  for (int i = 0; i < n; i++) {
    auto &p = pizza[i];
    bool b1 = find(p.list1, p.list1+p.m1, s1) != p.list1+p.m1;
    bool b2 = find(p.list2, p.list2+p.m2, s2) != p.list2+p.m2;
    if ((b1 && !b2) || (!b1 && b2)) {
      return false;
    }
  }

  return true;
}

void solve()
{
  cin >> n;

  for (int i = 0; i < n; i++) {
    pizza[i].read();
  }

  vector<pss> v;
  for (int i = 0; i < n; i++) {
    auto &p = pizza[i];
    for (int i1 = 0; i1 < p.m1; i1++) {
      for (int i2 = 0; i2 < p.m2; i2++) {
	string s1 = p.list1[i1], s2 = p.list2[i2];
	if (check(s1, s2)) {
	  v.emplace_back(s1, s2);
	}
      }
    }
  }
  sort(begin(v), end(v));
  v.resize(unique(begin(v), end(v)) - begin(v));
  for (auto p : v) {
    cout << "(" << p.first << ", " << p.second << ")" << endl;
  }
  
  cout << endl;
}

int main()
{
  int T;
  cin >> T;

  while (T--) {
    solve();
  }

  return 0;
}
