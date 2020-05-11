// the idea is to make sure that there is at least one piece, and that
// the number of MM and FF pieces are the same.  This can be proved
// formally if desired...

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool loop(const string &s)
{
  int MMcount = 0, FFcount = 0;
  
  istringstream is(s);
  string piece;
  int count = 0;
  while (is >> piece) {
    count++;
    if (piece == "MM") MMcount++;
    if (piece == "FF") FFcount++;
  }

  return count > 1 && MMcount == FFcount;
}

int main(void)
{
  int C;
  cin >> C;
  cin.ignore(1);
  while (C-- > 0) {
    string s;
    getline(cin, s);
    if (loop(s)) {
      cout << "LOOP" << endl;
    } else {
      cout << "NO LOOP" << endl;
    }
  }
  return 0;
}
