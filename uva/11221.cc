#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void solve()
{
  string line;
  getline(cin, line);
  for (int i = line.length()-1; i >= 0; i--) {
    if (!isalpha(line[i])) {
      line.erase(i, 1);
    }
  }
  for (int k = 1; k*k <= line.length(); k++) {
    if (k*k != line.length()) continue;

    string s;
    for (int i = 0; i < k; i++) {
      s += line.substr(i*k, k);
    }
    string t(s.rbegin(), s.rend());
    if (t != s) continue;
    
    s = "";
    for (int i = 0; i < k; i++) {
      for (int j = 0; j < k; j++) {
	s += line[j*k+i];
      }
    }
    t = s;
    reverse(t.begin(), t.end());
    if (t != s) continue;

    cout << k << endl;
    return;
  }
  cout << "No magic :(" << endl;
}

int main(void)
{
  int T;
  cin >> T;
  cin.ignore(1);
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ":" << endl;
    solve();
  }
  return 0;
}
