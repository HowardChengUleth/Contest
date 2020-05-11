/* @JUDGE_ID: 1102NT 10815 C++ "" */

#include <iostream>
#include <string>
#include <cctype>
#include <set>

using namespace std;

int main(void)
{
  set<string> dict;
  string line;

  while (getline(cin, line)) {
    unsigned int start = 0;
    line += " ";     // terminate the line with spaces so there is no need to 
                     // take care of the last word in the loop below
    for (unsigned int i = 0; i < line.length(); i++) {
      line[i] = tolower(line[i]);
      if (islower(line[i])) {
	
      } else {
	if (i != start) {
	  dict.insert(line.substr(start, i-start));
	}
	start = i+1;
      }
    }
  }
  for (set<string>::const_iterator it = dict.begin(); it != dict.end(); ++it) {
    cout << *it << endl;
  }
  return 0;
}
