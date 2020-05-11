//
// Standard parsing, except that when applying the operator, you just scan
// all the applicable entries in the truth table.  If you see only one type
// of answer, then you can return the answer.  Otherwise, return unknown.
//
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cassert>

using namespace std;

typedef vector<vector<int> > vvi;

// bool values: 0 = false, 1 = true, -1 = unknown

void read_entry(map<string, vvi> &ops, int rows)
{
  string name;
  cin >> name;
  vvi table(2);
  table[0].resize(2);
  table[1].resize(2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 2; j++) {
      string val;
      cin >> val;
      table[i][j] = (val == "true") ? 1 : 0;
    }
  }

  if (rows == 1) {
    table[1][0] = table[0][0];
    table[1][1] = table[0][1];
  }
  ops[name] = table;
}

// remove leading/trailing spaces...can be made more efficient
void strip(string &expr)
{
  while (expr.length() > 0 && expr[0] == ' ') {
    expr.erase(0, 1);
  }
  while (expr.length() > 0 && expr[expr.length()-1] == ' ') {
    expr.erase(expr.length()-1, 1);
  }
}

// get the operator name starting at the beginning of the expr, or return
// empty string if there is none.  Removes the operator from expr.
string get_op(string &expr)
{
  unsigned int k = 0;
  while (k < expr.length() && isupper(expr[k])) {
    k++;
  }
  string ans = expr.substr(0, k);
  expr.erase(0, k);
  return ans;
}

int apply(const vvi &table, int left, int right)
{
  bool has_true = false, has_false = false;
  
  for (int i = 0; i < 2; i++) {
    if (left != -1 && left != i) continue;
    for (int j = 0; j < 2; j++) {
      if (right != -1 && right != j) continue;
      has_true |= table[i][j];
      has_false |= !table[i][j];
    }
  }

  assert(has_true || has_false);
  if (has_true && has_false) return -1;
  if (has_true) return 1;
  return false;
}
	  
int eval(string expr, const map<string, vvi> &ops, const int value[])
{
  strip(expr);

  // single variable, base case
  if (islower(expr[0])) {
    assert(expr.length() == 1);
    return value[(unsigned char)expr[0]];
  }

  assert(expr[0] == '(' && expr[expr.length()-1] == ')');
  expr.erase(expr.length()-1, 1);
  expr.erase(0, 1);
  strip(expr);

  // see if it is a unary operator...can be made more efficient
  string op_name = get_op(expr);
  if (op_name != "") {
    // unary operator
    assert(ops.find(op_name) != ops.end());
    int op_val = eval(expr, ops, value);
    return apply(ops.find(op_name)->second, 0, op_val);
  }

  // must be binary operator, so look for one
  int level = 0;
  for (unsigned int i = 0; i < expr.length(); i++) {
    if (expr[i] == '(') level++;
    else if (expr[i] == ')') level--;
    if (isupper(expr[i]) && level == 0) {
      string left_expr = expr.substr(0, i);
      expr.erase(0, i);
      op_name = get_op(expr);
      assert(ops.find(op_name) != ops.end());
      int left_val = eval(left_expr, ops, value);
      int right_val = eval(expr, ops, value);
      return apply(ops.find(op_name)->second, left_val, right_val);
    }
  }

  // should not get here
  assert(false);
  return -1;
}
	 
bool solve(int id)
{
  int num_unary, num_binary;
  cin >> num_unary >> num_binary;
  if (num_unary < 0 && num_binary < 0) {
    return false;
  }

  // unary op: just replicate the row
  map<string, vvi> ops;

  // read unary ops
  for (int i = 0; i < num_unary; i++) {
    read_entry(ops, 1);
  }
  
  // read binary ops
  for (int i = 0; i < num_binary; i++) {
    read_entry(ops, 2);
  }

  string expr;
  getline(cin, expr);      // ignore until end of line
  getline(cin, expr);

  // assigned values of each variable
  int value[256];
  fill(value, value+256, -1);

  unsigned char c;
  while (cin >> c && c != '*') {
    string assign;
    cin >> assign;
    value[c] = (assign == "true");
  }

  int ans = eval(expr, ops, value);
  cout << "Case " << id << ": ";
  switch (ans) {
  case -1:
    cout << "unknown" << endl;
    break;
  case 0:
    cout << "false" << endl;
    break;
  case 1:
    cout << "true" << endl;
    break;
  }
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
