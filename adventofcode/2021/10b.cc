#include <bits/stdc++.h>

using namespace std;

bool corrupt(string s)
{
  stack<char> S;

  char match[256];
  match['('] = ')';
  match['['] = ']';
  match['{'] = '}';
  match['<'] = '>';
  
  for (auto c : s) {
    switch (c) {
    case '(':
    case '[':
    case '{':
    case '<':
      S.push(c);
      break;
    case ')':
    case ']':
    case '}':
    case '>':
      if (S.empty()) {
	assert(false);
      }
      if (match[S.top()] != c) {
	return true;
      }
      S.pop();
    }
  }

  return false;
}

typedef long long ll;

ll complete(string s)
{
  stack<char> S;

  int point[256];
  point[')'] = 1;
  point[']'] = 2;
  point['}'] = 3;
  point['>'] = 4;
  
  char match[256];
  match['('] = ')';
  match['['] = ']';
  match['{'] = '}';
  match['<'] = '>';
  
  for (auto c : s) {
    switch (c) {
    case '(':
    case '[':
    case '{':
    case '<':
      S.push(c);
      break;
    case ')':
    case ']':
    case '}':
    case '>':
      assert(match[S.top()] == c);
      S.pop();
    }
  }

  ll ans = 0;
  while (!S.empty()) {
    ans = 5*ans + point[match[S.top()]];
    S.pop();
  }
  return ans;
}



int main()
{
  string line;

  vector<ll> ans;
  while (cin >> line) {
    if (corrupt(line)) continue;
    ans.push_back(complete(line));
  }
  sort(begin(ans), end(ans));
  int n = ans.size();
  cout << ans[n/2] << endl;

  return 0;
}
