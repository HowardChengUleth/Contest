#include <list>
#include <string>
#include <iostream>

using namespace std;

int main(void)
{
  string s;
  while (getline(cin, s)) {
    list<char> L;
    list<char>::iterator it = L.begin();

    for (unsigned int i = 0; i < s.length(); i++) {
      if (s[i] == '[') {
	it = L.begin();
      } else if (s[i] == ']') {
	it = L.end();
      } else {
	L.insert(it, s[i]);
      }
    }

    for (it = L.begin(); it != L.end(); ++it) {
      cout << *it;
    }
    cout << endl;

  }

  return 0;
}
