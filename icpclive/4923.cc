#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

char map[256];

char do_map(char x)
{
  return map[(int)x];
}

int main(void)
{
  fill(map+'a', map+'z'+1, ' ');
  map['b'] = 'd';
  map['d'] = 'b';
  map['p'] = 'q';
  map['q'] = 'p';
  map['i'] = 'i';
  map['o'] = 'o';
  map['v'] = 'v';
  map['w'] = 'w';
  map['x'] = 'x';

  string s;
  while (getline(cin, s) && s != "#") {
    string t = s;
    transform(t.begin(), t.end(), t.begin(), do_map);
    if (t.find(' ') != string::npos) {
      cout << "INVALID" << endl;
      continue;
    }

    reverse(t.begin(), t.end());
    cout << t << endl;
  }

  return 0;
}
