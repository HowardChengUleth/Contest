//
// Straightforward: just do it.
//
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
  int N;
  cin >> N;

  while (N--) {
    string num;
    cin >> num;
    int first = 0, second = 0;

    for (int i = 0; i < 3; i++) {
      first = 26*first + num[i] - 'A';
    }

    for (int i = 4; i < 8; i++) {
      second = 10*second + num[i] - '0';
    }

    if (abs(first - second) <= 100) {
      cout << "nice" << endl;
    } else {
      cout << "not nice" << endl;
    }
  }
    
  return 0;
}
