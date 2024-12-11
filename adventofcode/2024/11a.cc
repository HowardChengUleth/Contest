#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> blink(const vector<ll> &v)
{
  vector<ll> v2;
  v2.reserve(v.size() * 2);
  
  for (auto x : v) {
    if (x == 0) {
      v2.push_back(1);
    } else {
      string s = to_string(x);
      if (s.length() % 2 == 0) {
	v2.push_back(stoll(s.substr(0, s.length()/2)));
	v2.push_back(stoll(s.substr(s.length()/2)));
      } else {
	v2.push_back(x * 2024);
      }
    }
  }
  return v2;
}

int main()
{
  vector<ll> v;
  int x;
  while (cin >> x) {
    v.push_back(x);
  }

  for (int i = 0; i < 25; i++) {
    v = blink(v);
    //    for (auto x : v) {
    //      cout << x << ' ';
    //    }
    //    cout << endl;
  }

  cout << v.size() << endl;

  return 0;
}
