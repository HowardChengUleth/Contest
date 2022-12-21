#include <bits/stdc++.h>

using namespace std;

struct Val
{
  string num;
  string operand1, operand2, op;   // op == "!" to mean number

  Val(string x = "0")
    : num{x}, op{"!"} { }
  Val(string O1, string O2, string OP)
    : operand1{O1}, operand2{O2}, op{OP} { }

  bool isNum() const {
    return op == "!";
  }
};

typedef long long ll;
map<string,Val> M;
map<string,string> memo;

string eval(const string &name)
{
  if (memo.find(name) != memo.end()) {
    return memo[name];
  }

  if (M[name].isNum()) {
    return memo[name] = M[name].num;
  }

  string operand1 = eval(M[name].operand1);
  string operand2 = eval(M[name].operand2);
  string ans = "(" + operand1 + M[name].op + operand2 + ")";
  return memo[name] = ans;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    replace(begin(line), end(line), ':', ' ');

    string name, operand1, operand2, op;

    istringstream iss(line);
    iss >> name;
    iss >> operand1;
    if (iss >> op >> operand2) {
      M[name] = Val(operand1, operand2, op);
    } else {
      M[name] = Val(operand1);
    }
  }

  M["root"].op = "-";
  M["humn"] = Val("x");

  string ans = eval("root");
  ans = "solve(" + ans + "= 0, x);";
  cout << ans << endl;

  // this is kind of cheating...generating Maple commands :)
  
  return 0;
}
