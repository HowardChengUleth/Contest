#include <bits/stdc++.h>

using namespace std;

const string keyboard = 
  "`1234567890-="
  "QWERTYUIOP[]\\"
  "ASDFGHJKL;'"
  "ZXCVBNM,./";

char lookup(char c)
{
  auto pos = keyboard.find(c);
  return (pos == string::npos) ? c : keyboard[pos-1];
}

int main()
{
  char c;

  while (cin.get(c)) {
    cout << lookup(c);
  }
  return 0;
}

