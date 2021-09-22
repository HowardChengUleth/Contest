#include <bits/stdc++.h>

using namespace std;

string finger[14] = {
  "0111001111",
  "0111001110",
  "0111001100",
  "0111001000",
  "0111000000",
  "0110000000",
  "0100000000",
  "0010000000",
  "1111001110",
  "1111001100",
  "1111001000",
  "1111000000",
  "1110000000",
  "1100000000"
};

string notemap = "cdefgabCDEFGAB";

string fingers(char note)
{
  int i;

  i = notemap.find(note);
  return finger[i];
}

int main(void)
{
  int t;

  cin >> t;
  cin.ignore();
  while (t-- > 0) {
    string buffer;
    string set = "0000000000", newset;
    int count[10] = {0};

    getline(cin, buffer);
    for (auto c : buffer) {
      newset = fingers(c);
      for (int i = 0; i < 10; i++) {
	if (newset[i] == '1' && set[i] == '0') {
	  count[i]++;
	}
      }
      set = newset;
    }

    for (int i = 0; i < 10; i++) {
      cout << count[i] << ' ';
    }
    cout << endl;
  }

  return 0;
}
