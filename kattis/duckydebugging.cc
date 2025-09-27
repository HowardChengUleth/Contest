#include <bits/stdc++.h>

using namespace std;

int main()
{
  string line;

  while (getline(cin, line) && line != "I quacked the code!") {
    if (line.back() == '?') {
      cout << "Quack!" << endl;
    } else {
      cout << "*Nod*" << endl;
    }
  }

  return 0;
}
