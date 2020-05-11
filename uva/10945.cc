#include <string>
#include <iostream>
#include <cctype>

using namespace std;

bool palindrome(string s)
{
  int i, j;

  i = 0;
  j = s.length()-1;

  while (i < j) {
    while (!isalpha(s[i]) && i < j) i++;
    while (!isalpha(s[j]) && i < j) j--;
    if (i < j && tolower(s[i]) != tolower(s[j])) {
      return false;
    }
    i++; j--;
  }
  return true;
}

int main(void)
{
  string s;

  while (getline(cin, s) && s != "DONE") {
    if (palindrome(s)) {
      cout << "You won't be eaten!" << endl;
    } else {
      cout << "Uh oh.." << endl;
    }
  }

  return 0;
}
