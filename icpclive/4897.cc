#include <iostream>
#include <string>

using namespace std;

string keys[10] = { "", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV",
		    "WXYZ" };

void totext(string line)
{
  char prev_key = 'X';
  char next_key;
  int rep;
  for (unsigned int i = 0; i < line.length(); i++) {
    if (line[i] == ' ') {
      next_key = '#';
      rep = 1;
    } else {
      for (int key = 2; key <= 9; key++) {
	unsigned int pos;
	if ((pos = keys[key].find(line[i])) != string::npos) {
	  next_key = '0' + key;
	  rep = pos+1;
	}
      }
    }

    if (next_key == prev_key) {
      cout << 'P';
    }
    if (i > 0) cout << '-';
    for (int j = 0; j < rep; j++) {
      cout << next_key;
    }
    prev_key = next_key;
  }
}

void toplain(string line)
{
  line += '-';
  unsigned int pos = -1, newpos;
  
  while ((newpos = line.find('-', pos+1)) != string::npos) {
    string key = line.substr(pos+1, newpos-pos-1);
    if (key[0] == '#') {
      cout << ' ';
    } else {
      int k = key[0] - '0';
      int len = key.length();
      if (key[len-1] == 'P') len--;
      cout << keys[k][len-1];
    }
    pos = newpos;
  }
}

int main(void)
{
  string line;

  while (getline(cin, line) && line[0] != '*') {
    if (line[0] == ' ' || isupper(line[0])) {
      totext(line);
    } else {
      toplain(line);
    }
    cout << endl;
  }

  return 0;
}
