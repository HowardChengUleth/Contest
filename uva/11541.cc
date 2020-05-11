#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(void)
{
  int T;
  cin >> T;

  for (int i = 1; i <= T; i++) {
    string s;
    cin >> s;
    istringstream iss(s);

    cout << "Case " << i << ": ";
    char c;
    int count;
    while (iss >> c >> count) {
      for (int j = 0; j < count; j++) {
	cout << c;
      }
    }
    cout << endl;
  }
  return 0;
}
