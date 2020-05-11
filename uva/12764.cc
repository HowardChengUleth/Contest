// Not much to say...just do it and be careful.
//

#include <iostream>
#include <string>

using namespace std;


string frame[10][3] = {
  { "\\ / ",
    " |  ",
    "/o\\ "},
  { " o  ",
    "/|\\ ",
    "/ \\ "},
  { "    ",
    "    ",
    "__\\o"},
  { "    ",
    "    ",
    "\\_\\o"},
  { "_o_ ",
    " |  ",
    "/ \\ "},
  { "\\o/ ",
    " |  ",
    "/ \\ " },
  { "\\o_ ",
    "\\|  ",
    " |  "},
  { "\\o/ ",
    "\\|/ ",
    "    "},
  { "    ",
    " __o",
    "/  |"},
  { " o  ",
    "( ) ",
    "/ \\ "}
};

void solve()
{
  string s;
  cin >> s;
  for (int r = 0; r < 3; r++) {
    for (int i = 0; i < s.length(); i++) {
      if (i) cout << ' ';
      cout << frame[s[i]-'0'][r];
    }
    cout << endl;
  }

  cout << endl;
}

int main()
{
  int M;
  cin >> M;
  while (M--)
    solve();
  return 0;
}
