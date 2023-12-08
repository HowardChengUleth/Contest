#include <bits/stdc++.h>

using namespace std;

typedef pair<string, string> pss;
map<string, pss> G;

bool read_node()
{
  string line;
  getline(cin, line);
  if (cin.eof()) return false;

  for (auto &c : line) {
    if (!isalpha(c)) c = ' ';
  }
  
  istringstream iss(line);
  string from, left, right;
  iss >> from >> left >> right;
  G[from] = make_pair(left, right);

  return true;
}

string dir;

int count_steps(const string &from, const string &to, int index = 0)
{
  if (index >= dir.length()) {
    index = 0;
  }
  if (from == to) return 0;

  string next = (dir[index] == 'L') ? G[from].first : G[from].second;
  return 1 + count_steps(next, to, index+1);
}

int main()
{
  cin >> dir;

  string str;
  getline(cin, str);
  getline(cin, str);
  while (read_node())
    ;

  cout << count_steps("AAA", "ZZZ") << endl;
  
  return 0;
}
