#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll evalA(string e)
{
  int level = 0;
  
  for (int i = e.length()-1; i >= 0; i--) {
    char c = e[i];
    if (c == ')') level++;
    else if (c == '(') level--;
    else if (c == '+' && !level) {
      return evalA(e.substr(0, i)) + evalA(e.substr(i+1));
    } else if (c == '*' && !level) {
      return evalA(e.substr(0, i)) * evalA(e.substr(i+1));
    }
  }
  if (e[0] == '(') {
    return evalA(e.substr(1, e.length()-2));
  }

  return stoll(e);
}

ll evalB(string e)
{
  int level = 0;
  
  for (int i = e.length()-1; i >= 0; i--) {
    char c = e[i];
    if (c == ')') level++;
    else if (c == '(') level--;
    else if (c == '*' && !level) {
      return evalB(e.substr(0, i)) * evalB(e.substr(i+1));
    }
  }

  for (int i = e.length()-1; i >= 0; i--) {
    char c = e[i];
    if (c == ')') level++;
    else if (c == '(') level--;
    else if (c == '+' && !level) {
      return evalB(e.substr(0, i)) + evalB(e.substr(i+1));
    }
  }
  if (e[0] == '(') {
    return evalB(e.substr(1, e.length()-2));
  }

  return stoll(e);
}

int main()
{
  string line;
  vector<string> expr;

  while (getline(cin, line)) {
    for (int i = line.length()-1; i >= 0; i--) {
      if (line[i] == ' ') {
	line.erase(i, 1);
      }
    }
    expr.push_back(line);
  }

  long long ansA = 0;
  for (auto e : expr) {
    ansA += evalA(e);
  }
  cout << "A = " << ansA << endl;

  long long ansB = 0;
  for (auto e : expr) {
    ansB += evalB(e);
  }
  cout << "B = " << ansB << endl;

  return 0;
}
