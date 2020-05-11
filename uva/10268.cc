#include <iostream>
#include <sstream>
#include <deque>
#include <vector>

using namespace std;

int main(void)
{
  int x;
  while (cin >> x) {
    deque<int> coeffs;
    string line;
    getline(cin, line);
    getline(cin, line);
    istringstream iss(line);
    int c;
    while (iss >> c) {
      coeffs.push_front(c);
    }

    vector<int> deriv(coeffs.size()-1);
    for (int i = 0; i < coeffs.size()-1; i++) {
      deriv[i] = (i+1)*coeffs[i+1];
    }

    int ans = 0;
    for (int i = deriv.size()-1; i >= 0; i--) {
      ans = ans * x + deriv[i];
    }

    cout << ans << endl;
  }
  return 0;
}
