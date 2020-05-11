#include <iostream>
#include <set>
#include <string>

using namespace std;

void solve(const string &s1, const string &s2)
{
  int n1 = s1.length(), n2 = s2.length();
  int len[301][301];

  for (int i = 0; i <= n1; i++) {
    len[i][0] = 0;
  }
  for (int j = 0; j <= n2; j++) {
    len[0][j] = 0;
  }

  int best = 0;
  for (int i = 1; i <= n1; i++) {
    for (int j = 1; j <= n2; j++) {
      if (s1[i-1] != s2[j-1]) {
	len[i][j] = 0;
      } else {
	len[i][j] = 1 + len[i-1][j-1];
      }
      best = max(best, len[i][j]);
    }
  }

  if (best == 0) {
    cout << "No common sequence." << endl;
  } else {
    set<string> S;
    for (int i = 1; i <= n1; i++) {
      for (int j = 1; j <= n2; j++) {
	if (len[i][j] != best) continue;
	S.insert(s1.substr(i-best, best));
      }
    }

    for (set<string>::const_iterator it = S.begin(); it != S.end(); ++it) {
      cout << *it << endl;
    }
  }
}

int main(void)
{
  string s1, s2;
  bool first = true;
  while (cin >> s1 >> s2) {
    if (!first) cout << endl;
    solve(s1, s2);
    first = false;
  }
  
  return 0;
}
