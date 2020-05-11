#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

int main(void)
{
  int S, C;
  int id = 1;
  while (cin >> C >> S) {
    cout << "Set #" << id++ << endl;

    int A[10];
    double avg = 0;
    for (int i = 0; i < S; i++) {
      cin >> A[i];
      avg += A[i];
    }
    for (int i = S; i < 2*C; i++) {
      A[i] = 0;
    }
    avg /= C;
    sort(A, A + 2*C);

    double imb = 0.0;
    for (int i = 0; i < C; i++) {
      cout << ' ' << i << ":";
      if (A[i]) cout << ' ' << A[i];
      if (A[2*C-1-i]) cout << ' ' << A[2*C-1-i];
      cout << endl;

      imb += fabs(A[i] + A[2*C-1-i] - avg);
    }
    
    cout << "IMBALANCE = " << fixed << setprecision(5) << imb << endl << endl;
  }
  return 0;
}
