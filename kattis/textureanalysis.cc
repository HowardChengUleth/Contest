#include <bits/stdc++.h>

using namespace std;

void solve(int id, const string &s)
{
  cout << id << " ";
  
  int last = 0;
  int old_gap = -1;
  for (int i = 1; i < s.length(); i++) {
    if (s[i] == '*') {
      int gap = i - last - 1;
      if (old_gap == -1) {
	old_gap = gap;
      } else if (gap != old_gap) {
	cout << "NOT EVEN" << endl;
	return;
      }
      last = i;
    }
    
  }

  cout << "EVEN" << endl;
}

int main()
{
  string s;
  int id = 1;
  while (getline(cin, s) && s != "END") {
    solve(id++, s);
  }

  return 0;
}
