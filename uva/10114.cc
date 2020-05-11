#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int months, num_dep;
  double down, loan;

  while (cin >> months >> down >> loan >> num_dep && months >= 0) {
    double dep[101];
    fill(dep, dep+months+1, -1);
    for (int i = 0; i < num_dep; i++) {
      int m;
      double r;
      cin >> m >> r;
      dep[m] = 1-r;
    }
    for (int i = 0; i <= months; i++) {
      if (dep[i] < 0) {
	dep[i] = dep[i-1];
      }
    }

    double payment = loan/months;
    double val = (down+loan) * dep[0];
    int i = 0;

    //    cout << "i = " << i << ": " << val << endl;
    while (val <= loan) {
      loan -= payment;
      val *= dep[i+1];
      i++;
      //      cout << "i = " << i << ": " << val << endl;
    }
    
    cout << i << " month";
    if (i != 1) cout << "s";
    cout << endl;
  }

  return 0;
}
