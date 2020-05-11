#include <iostream>
#include <string>

using namespace std;

int main(void)
{
  string s;
  while (getline(cin, s) && s != "#") {
    int ycount = 0, ncount = 0, acount = 0;

    for (unsigned int i = 0; i < s.length(); i++) {
      switch (s[i]) {
      case 'Y':
	ycount++;
	break;
      case 'N':
	ncount++;
	break;
      case 'A':
	acount++;
	break;
      }
    }

    int n = s.length();
    if (acount >= (n+1)/2) {
      cout << "need quorum" << endl;
    } else if (ycount > ncount) {
      cout << "yes" << endl;
    } else if (ncount > ycount) {
      cout << "no" << endl;
    } else {
      cout << "tie" << endl;
    }
  }
  return 0;
}
