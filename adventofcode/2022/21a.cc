#include <bits/stdc++.h>

using namespace std;

struct Val
{
  int num;
  string operand1, operand2, op;   // op == "!" to mean number

  Val(int x = 0)
    : num{x}, op{"!"} { }
  Val(string O1, string O2, string OP)
    : operand1{O1}, operand2{O2}, op{OP} { }

  bool isNum() const {
    return op == "!";
  }
};

typedef long long ll;
map<string,Val> M;
map<string,ll> memo;

ll eval(const string &name)
{
  if (memo.find(name) != memo.end()) {
    return memo[name];
  }

  if (M[name].isNum()) {
    return memo[name] = M[name].num;
  }

  ll operand1 = eval(M[name].operand1);
  ll operand2 = eval(M[name].operand2);
  ll ans;
  if (M[name].op == "+") {
    ans = operand1 + operand2;
  } else if (M[name].op == "-") {
    ans = operand1 - operand2;
  } else if (M[name].op == "*") {
    ans = operand1 * operand2;
  } else if (M[name].op == "/") {
    ans = operand1 / operand2;
  } else {
    cout << name << endl;
    cout << M[name].op << endl;
    assert(false);
  }

  return memo[name] = ans;

}

int main()
{
  string line;
  while (getline(cin, line)) {
    replace(begin(line), end(line), ':', ' ');

    string name, operand1, operand2, op;
    int num;

    istringstream iss(line);
    iss >> name;
    if (iss >> num) {
      M[name] = Val(num);
    } else {
      iss.clear();
      iss >> operand1 >> op >> operand2;
      M[name] = Val(operand1, operand2, op);
    }
  }

  ll ans = eval("root");
  cout << ans << endl;
  
  return 0;
}
