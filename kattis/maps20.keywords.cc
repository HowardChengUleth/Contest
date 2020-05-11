#include <bits/stdc++.h>

using namespace std;

int main()
{
  set<string> S;

  int n;
  cin >> n;
  cin.ignore();
  while (n--) {
    string w;
    getline(cin, w);
    for (auto &ch : w) {
      ch = tolower(ch);
      if (ch == '-') {
	ch = ' ';
      }
    }
    S.insert(w);
  }
  cout << S.size() << endl;

  return 0;
}
