#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

void solve(const string &num)
{
  int pos = num.find('e');
  string mant_str = num.substr(0, pos),
    exp_str = num.substr(pos+1);

  istringstream iss1(mant_str), iss2(exp_str);

  long double mant, ex;
  iss1 >> mant;
  iss2 >> ex;


  long double log2num = (log(mant) + ex*logl(10.0)) / logl(2.0);

  int bestM = -1, bestE = -1;
  long double best_diff;

  for (int E = 1; E <= 30; E++) {
    long double test_mant = 0;
    long double term = 0.5;
    for (int M = 0; M <= 9; M++) {
      test_mant += term;
      
      long double log2test = log(test_mant)/logl(2.0) + (powl(2, E) - 1);
      long double diff = fabs(log2test - log2num);
      //    cout << "M = " << M << ", diff = " << diff << ", log2test = "
      //	 << log2test << endl;
      if (bestM < 0 || diff < best_diff) {
	bestM = M;
	bestE = E;
	best_diff = diff;
      }
      
      term *= 0.5;
    }
  }

  
  cout << bestM << ' ' << bestE << endl;
}

int main()
{
  string num;

  while (cin >> num && num != "0e0") {
    solve(num);
  }
  
  return 0;
}
