#include <iostream>
#include <string>

using namespace std;

int main(void)
{
  int N;
  cin >> N;
  while (N--) {
    string s;
    cin >> s;
    if (s.length() == 5) {
      cout << 3 << endl;
    } else {
      int correct = 0;
      correct += s[0] == 'o';
      correct += s[1] == 'n';
      correct += s[2] == 'e';
      if (correct >= 2) {
	cout << 1 << endl;
      } else {
	cout << 2 << endl;
      }
    }
  }
  return 0;
}
