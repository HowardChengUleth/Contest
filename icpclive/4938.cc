// just do it

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

char decode(char c, char k)
{
  int ci = (c == ' ') ? 26 : c - 'A';
  int ki = (k == ' ') ? 26 : k - 'A';
  
  ci = (ci + (27 - ki)) % 27;
  if (ci == 26) return ' ';
  return ci + 'a';
}

int main(void)
{
  string key, shift, line;
  
  getline(cin, line);
  int pos = line.find(':');
  key = line.substr(0, pos);
  shift = line.substr(pos+1);

  while (getline(cin, line)) {
    int shift_pos = 0, shift_count = 0;

    for (int i = 0; i < line.length(); i++) {
      line[i] = decode(line[i], key[shift_pos]);
      if (++shift_count >= shift[shift_pos] - '0') {
	if (++shift_pos >= shift.length()) {
	  shift_pos = 0;
	}
	shift_count = 0;
      }
    }
    cout << line << endl;
  }

  return 0;
}
