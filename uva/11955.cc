#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void print(long long coeff, const string &var1, const string &var2,
	   int exp1, int exp2)
{
  if (coeff > 1) {
    cout << coeff << '*';
  }

  if (exp1 > 0) {
    cout << var1;
    if (exp1 > 1) {
      cout << '^' << exp1;
    }
  }
  if (exp1 > 0 && exp2 > 0) {
    cout << '*';
  }
  if (exp2 > 0) {
    cout << var2;
    if (exp2 > 1) {
      cout << '^' << exp2;
    }
  }
}

long long binom[51][51];

void solve(const string &line)
{
  int open = 0;
  int close = line.find(')');
  int plus = line.find('+');

  string var1 = line.substr(open+1, plus-(open+1));
  string var2 = line.substr(plus+1, close-(plus+1));
  int exp = atoi(line.substr(line.find('^')+1).c_str());

  for (int i = exp; i >= 0; i--) {
    print(binom[exp][i], var1, var2, i, exp-i);
    if (i) cout << '+';
  }
  cout << endl;
}

int main(void)
{
  for (int n = 0; n <= 50; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (int k = 1; k <= n-1; k++) {
      binom[n][k] = binom[n-1][k] + binom[n-1][k-1];
    }
  }

  
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    string line;
    cin >> line;
    solve(line);
  }

  return 0;
}
