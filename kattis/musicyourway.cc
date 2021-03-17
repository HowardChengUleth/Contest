#include <bits/stdc++.h>

using namespace std;

vector<string> attr;
vector<vector<string>> song;
int key;

bool cmp(const vector<string> &s1, const vector<string> &s2)
{
  return s1[key] < s2[key];
}

void print()
{
  for (auto s : attr) {
    cout << s << ' ';
  }
  cout << endl;
  for (auto v : song) {
    for (auto s : v) {
      cout << s << ' ';
    }
    cout << endl;
  }
  cout << endl;
}

int main()
{
  string s;
  getline(cin, s);
  istringstream iss(s);
  while (iss >> s) {
    attr.push_back(s);
  }

  int m;
  cin >> m;

  for (int i = 0; i < m; i++) {
    vector<string> v;
    for (int i = 0; i < attr.size(); i++) {
      cin >> s;
      v.push_back(s);
    }
    song.push_back(v);
  }
  
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string a;
    cin >> a;
    key = find(begin(attr), end(attr), a) - begin(attr);
    stable_sort(begin(song), end(song), cmp);
    print();
  }

  return 0;
}
