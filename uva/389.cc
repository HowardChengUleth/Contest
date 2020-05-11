#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

int main(void)
{
  string sin, sout;
  int from, to;

  while (cin >> sin >> from >> to) {
    int num = 0;
    for (unsigned int i = 0; i < sin.length(); i++) {
      num *= from;
      if (isdigit(sin[i])) {
	num += sin[i] - '0';
      } else {
	num += sin[i] - 'A' + 10;
      }
    }
    sout = "";
    while (num) {
      char c;
      int d = num % to;
      num /= to;
      c = (d < 10) ? d + '0' : d - 10 + 'A';
      sout = c + sout;
    }
    if (sout == "") {
      sout = "0";
    }
    if (sout.length() > 7) {
      cout << setw(7) << "ERROR" << endl;
    } else {
      cout << setw(7) << sout << endl;
    }
  }
  return 0;
}
