#include <bits/stdc++.h>

using namespace std;

set<string> known;

bool check_line()
{
  string line;
  getline(cin, line);

  istringstream iss(line);
  bool seen_arrow = false;
  string s;
  while (iss >> s) {
    if (s == "->") {
      seen_arrow = true;
    } else if (!seen_arrow) {
      // assumption
      if (known.find(s) == known.end()) {
	return false;
      }
    } else {
      // conclusion
      known.insert(s);
    }
  }
    
  return true;
}

int main()
{
  int n;
  cin >> n;
  cin.ignore(1);

  for (int i = 1; i <= n; i++) {
    if (!check_line()) {
      cout << i << endl;
      return 0;
    }
  }

  cout << "correct" << endl;

  return 0;
}
