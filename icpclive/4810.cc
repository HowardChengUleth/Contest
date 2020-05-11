#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

int main()
{
  string line;
  while (getline(cin, line) && line != "*") {
    istringstream iss(line);
    string w;
    char start = ' ';
    bool good = true;
    while (iss >> w) {
      if (start != ' ') {
	good &= start == tolower(w[0]);
      }
      start = tolower(w[0]);
    }

    cout << (good ? "Y" : "N") << endl;
  }

  return 0;
}

