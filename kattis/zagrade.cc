#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  cin >> s;

  int id[201];
  fill(id, id+201, -1);

  stack<int> open_pos;
  int n = s.length();
  int curr = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') {
      open_pos.push(i);
    } else if (s[i] == ')') {
      id[i] = id[open_pos.top()] = curr++;
      open_pos.pop();
    }
  }

  set<string> ans;
  for (int m = 0; m < (1ULL << curr)-1; m++) {
    string temp;
    for (int i = 0; i < n; i++) {
      if ((s[i] != '(' && s[i] != ')') ||
	  ((1ULL << id[i]) & m)) {
	temp += s[i];
      }
    }
    ans.insert(temp);
  }

  for (auto s : ans) {
    cout << s << endl;
  }
  
  return 0;
}
