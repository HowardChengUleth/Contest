/* @JUDGE_ID: 1102NT 10340 C++ "" */

#include <string>
#include <iostream>

using namespace std;

int main(void)
{
  string s1, s2;

  while (cin >> s1 >> s2) {
    int i, j = 0;
    for (i = 0; i < s1.length(); i++) {
      if ((j = s2.find(s1[i], j)) == string::npos) {
	break;
      }
      j++;
    }
    cout << ((i == s1.length()) ? "Yes" : "No") << endl;
  }
  return 0;
}
