#include <bits/stdc++.h>

using namespace std;

typedef pair<string,int> psi;

priority_queue<psi, vector<psi>, greater<psi>> unread;
pair<int, psi> friends[100000];

string read_str()
{
  string s;
  char c;

  while (cin.get(c) && c != '"')
    ;
  while (cin.get(c) && c != '"') {
    s += c;
  }
  return s;
}

int main()
{
  int n, m, k;
  cin >> n >> m >> k;

  unread.emplace("Jane Eyre", k);
  for (int i = 0; i < n; i++) {
    int p;
    string s = read_str();
    cin >> p;
    unread.emplace(s, p);
  }

  for (int i = 0; i < m; i++) {
    int t, p;
    cin >> t;
    string s = read_str();
    cin >> p;
    friends[i] = make_pair(t, psi(s, p));
  }
  sort(friends, friends+m);

  // simulate
  long long t = 0;
  int fi = 0;
  while (!(unread.empty() && fi < m)) {
    while (fi < m && friends[fi].first <= t) {
      unread.push(friends[fi].second);
      fi++;
    }

    auto book = unread.top();
    unread.pop();
    t += book.second;
    if (book.first == "Jane Eyre") {
      cout << t << endl;
      break;
    }
  }
  
  return 0;
}
