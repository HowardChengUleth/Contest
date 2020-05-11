#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

bool palindrome(int curr)
{
  ostringstream oss;

  int h = curr / 60;
  int m = curr % 60;

  if (h) {
    oss << h << setfill('0') << setw(2) << m;
  } else {
    oss << m;
  }
  string s = oss.str();
  for (int i = 0; i < s.length()-1; i++) {
    if (s[i] != s[s.length()-1-i]) {
      return false;
    }
  }
  return true;

}

int main(void)
{
  int n;
  cin >> n;
  while (n-- > 0) {
    int h, m;
    cin >> h;
    cin.ignore(1);
    cin >> m;

    int curr = h*60+m+1;
    while (true) {
      curr %= (24*60);
      if (palindrome(curr)) {
	cout << setfill('0') << setw(2) << curr/60
	     << ':' 
	     << setfill('0') << setw(2) << curr%60 << endl;
	break;
      }
      curr++;
    }
  }

  return 0;
}
