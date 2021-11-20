#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool check(string s)
{
  for (int i = 1; i < s.length(); i++) {
    if (!islower(s[i])) {
      return false;
    }
  }
  return true;
}

int main()
{
  int P, T;
  cin >> P >> T;

  int solved = 0;
  for (int prob = 0; prob < P; prob++) {
    bool good = true;
    for (int line = 0; line < T; line++) {
      string s;
      cin >> s;
      if (!check(s)) {
	good = false;
      }
    }
    if (good) {
      solved++;
    }
  }

  cout << solved << endl;
  
  return 0;
}
