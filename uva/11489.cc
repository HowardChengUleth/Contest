#include <iostream>
#include <string>

using namespace std;

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";

    int num[3] = {0};
    int sum = 0;
    string s;
    cin >> s;
    for (int j = 0; j < s.length(); j++) {
      sum = (sum + (s[j] - '0')) % 3;
      num[(s[j]-'0') % 3]++;
    }

    if (sum > 0) {
      if (num[sum] == 0) {
	cout << "T" << endl;
      } else if (num[0] % 2 == 0) {
	cout << "S" << endl;
      } else {
	cout << "T" << endl;
      }
    } else if (num[0] % 2 == 0) {
      cout << "T" << endl;
    } else {
      cout << "S" << endl;
    }
  }

  return 0;
}
