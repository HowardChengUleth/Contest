#include <bits/stdc++.h>

using namespace std;

void solve()
{
  list<char> L;
  auto cursor = L.begin();

  string line;
  getline(cin, line);

  for (auto ch : line) {
    switch (ch) {
    case '[':
      cursor = L.begin();
      break;
    case ']':
      cursor = L.end();
      break;
    case '<':
      if (cursor != L.begin()) {
	cursor--;
	cursor = L.erase(cursor);
      }
      break;

    default:
      L.insert(cursor, ch);
    }
  }

  for (auto ch : L) {
    cout << ch;
  }
  cout << endl;
}

int main()
{
  int T;
  cin >> T;

  string line;
  getline(cin, line);
  for (int i = 0; i < T; i++) {
    solve();
  }

  return 0;
}
