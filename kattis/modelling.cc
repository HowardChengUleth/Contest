#include <bits/stdc++.h>

using namespace std;

bool eval(string prog, int table[256]);

void assignment(string prog, int table[256])
{
  int lhs = prog[0];
  assert(prog[1] == '=');

  int val;
  if (isdigit(prog[2])) {
    val = stoi(prog.substr(2));
  } else {
    int v1 = prog[2], v2 = prog[4];
    assert(prog[3] == '+');
    val = table[v1] + table[v2];
  }
  table[lhs] = val;
}

bool cond(string prog, int table[256])
{
  int v1 = prog[0], v2 = prog[2];
  assert(prog[1] == '<');
  if (table[v1] >= table[v2]) return true;
  assert(prog[3] == '{' && prog[prog.length()-1] == '}');
  return eval(prog.substr(4, prog.length()-5), table);
}

bool assertion(string prog, int table[256])
{
  int v1 = prog[0], v2 = prog[2];
  assert(prog.length() == 3 && prog[1] == '=');
  return table[v1] == table[v2];
}

bool eval(string prog, int table[256])
{
  if (prog.length() == 0) return true;
  int pos;
  if (prog[0] == '[') {
    pos = prog.find(']');
    assert(pos != string::npos);
    assignment(prog.substr(1, pos-1), table);
  } else if (prog[0] == '(') {
    pos = prog.find(')');
    assert(pos != string::npos);
    if (!cond(prog.substr(1, pos-1), table)) {
      return false;
    }
  } else if (prog[0] == '<') {
    pos = prog.find('>');
    assert(pos != string::npos);
    if (!assertion(prog.substr(1, pos-1), table)) {
      return false;
    }
  } else {
    assert(false);
  }
  return eval(prog.substr(pos+1), table);
}

bool check_assert(string prog, int index)
{
  while (index < prog.length() && prog[index] != '?')
    index++;

  if (index >= prog.length()) {
    int table[256] = {0};
    return eval(prog, table);
  }

  prog[index] = '1';
  bool ans1 = check_assert(prog, index+1);
  bool ans2 = false;
  if (ans1) {
    prog[index] = '0';
    ans2 = check_assert(prog, index+1);
  }
  prog[index] = '?';
  return ans1 && ans2;
}

void solve()
{
  string prog;
  cin >> prog;

  if (check_assert(prog, 0)) {
    cout << "ASSERTIONS ALWAYS HOLD" << endl;
  } else {
    cout << "ASSERTIONS INVALID" << endl;
  }
}

int main()
{
  int T;
  cin >> T;

  while (T--)
    solve();

  return 0;
}
