#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

typedef pair<char, char> pcc;

bool valid(string line)
{
  queue<pcc> q;

  q.push(pcc('A', 'Z'));
  int pos = 0;
  while (!q.empty()) {
    pcc curr = q.front();
    q.pop();

    // get to first (
    while (pos < line.length() && line[pos] != '(')
      pos++;
    pos++;
    if (pos >= line.length()) return false;

    while (pos < line.length() && isspace(line[pos]))
      pos++;
    if (pos >= line.length()) return false;

    char last = 0;
    while (pos < line.length() && line[pos] != ')') {
      if (!(curr.first <= line[pos] && line[pos] <= curr.second))
	return false;
      if (!(last < line[pos]))
	return false;
      q.push(pcc(max(curr.first, (char)(last+1)), line[pos]));
      last = line[pos++];
      while (pos < line.length() && isspace(line[pos]))
	pos++;
    }
    pos++;
    if (last > 0) {
      q.push(pcc(last+1, curr.second));
    }
  }

  while (pos < line.length() && isspace(line[pos]))
    pos++;
  if (pos < line.length()) {
    return false;
  }
  
  return true;
}

bool solve()
{
  string line;
  getline(cin, line);
  if (line.find('0') != string::npos) return false;

  bool printed = false;
  int pos = line.find('?');
  for (char i = 'A'; i <= 'Z'; i++) {
    line[pos] = i;
    if (valid(line)) {
      if (printed) cout << ' ';
      cout << i;
      printed = true;
    }
  }
  if (!printed) {
    cout << "This is not a myTree";
  }
  cout << endl;

  return true;
}

int main()
{
  while (solve())
    ;
  
  return 0;
}
