#include <bits/stdc++.h>

using namespace std;

void solve()
{
  string line;
  getline(cin, line);
  istringstream iss(line);

  string w;
  vector<string> rec;
  while (iss >> w) {
    rec.push_back(w);
  }

  set<string> bad;
  while (getline(cin, line) && line != "what does the fox say?") {
    istringstream iss2(line);
    string w1, w2, w3;
    iss2 >> w1 >> w2 >> w3;
    bad.insert(w3);
  }

  for (auto w : rec) {
    if (bad.count(w) == 0) {
      cout << w << ' ';
    }
  }
  cout << endl;

}

int main()
{
  int T;
  cin >> T;
  cin.ignore();
  while (T--)
    solve();

  return 0;
}
