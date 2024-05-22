// just try all possible operators in each of the three positions (there
// are 4^3 = 64 possibilities).  Then we have to evaluate them
#include <iostream>

using namespace std;

// 0 = +
// 1 = -
// 2 = *
// 3 = /
const char *opstr = "+-*/";

int eval(int op[], int k)
{
  if (k == 0) return 4;    // no operator, just 4

  // look for rightmost + or - (last op to be done)
  for (int i = k-1; i >= 0; i--) {
    if (op[i] == 0) {
      return eval(op, i) + eval(op+i+1, k-i-1);
    } else if (op[i] == 1) {
      return eval(op, i) - eval(op+i+1, k-i-1);
    }
  }

  // if there are no + or -, look for rightmost * or /
  for (int i = k-1; i >= 0; i--) {
    if (op[i] == 2) {
      return eval(op, i) * eval(op+i+1, k-i-1);
    } else if (op[i] == 3) {
      return eval(op, i) / eval(op+i+1, k-i-1);
    }
  }
}

void solve()
{
  int n;
  cin >> n;

  // only store the operators since the operands are always 4
  int op[3];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
	op[0] = i;
	op[1] = j;
	op[2] = k;
	if (eval(op, 3) == n) {
	  cout << "4";
	  for (int i = 0; i < 3; i++) {
	    cout << ' ' << opstr[op[i]] << " 4";
	  }
	  cout << " = " << n << endl;
	  return;
	}
      }
    }
  }

  cout << "no solution" << endl;
}

int main()
{
  int m;
  cin >> m;
  while (m--) {
    solve();
  }

  return 0;
}
