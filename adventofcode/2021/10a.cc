#include <bits/stdc++.h>

using namespace std;

int score(string s)
{
  stack<char> S;

  int point[256];
  point[')'] = 3;
  point[']'] = 57;
  point['}'] = 1197;
  point['>'] = 25137;
  
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
	cout << s << " : " << c << ' ' << S.top() << endl;
	return point[c];
      }
      S.pop();
    }
  }

  if (!S.empty()) {
    // incomplete
  }
  return 0;
}

int main()
{
  string line;
  int ans = 0;
  while (cin >> line) {
    ans += score(line);
  }
  cout << ans << endl;

  return 0;
}
