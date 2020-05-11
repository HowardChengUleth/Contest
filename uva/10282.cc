#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int main(void)
{
  string line;
  map<string,string> dict;

  while (getline(cin, line) && line.length() > 0) {
    istringstream is(line);
    string to, from;
    is >> to >> from;
    dict[from] = to;
  }
  
  while (cin >> line) {
    if (dict.find(line) == dict.end()) {
      cout << "eh" << endl;
    } else {
      cout << dict[line] << endl;
    }
  }
  return 0;
}
