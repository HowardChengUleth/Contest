#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

int main(void)
{
  int k;

  while (cin >> k) {
    cin.ignore(1);

    string line;
    getline(cin, line);
    istringstream iss(line);
    
    long long A[10002];
    int deg = -1;
    while (iss >> A[deg+1]) {
      deg++;
    }
    reverse(A, A+deg+1);

    long long Q[10002];
    fill(Q, Q+deg+1, 0);

    for (int i = deg; i >= 1; i--) {
      Q[i-1] = A[i];
      A[i-1] += A[i]*k;
    }

    cout << "q(x):";
    for (int i = deg-1; i >= 0; i--) {
      cout << ' ' << Q[i];
    }
    cout << endl;
    cout << "r = " << A[0] << endl;
    cout << endl;

  }
  return 0;
}
