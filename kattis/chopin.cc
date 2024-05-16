#include <bits/stdc++.h>

using namespace std;

typedef pair<string, string> pss;

string other_note(string note)
{
  if (note.length() < 2) return "";
  if (note[1] == '#') {
    if (++note[0] > 'G') {
      note[0] = 'A';
    }
    note[1] = 'b';
  } else {
    if (--note[0] < 'A') {
      note[0] = 'G';
    }
    note[1] = '#';
  }
  return note;
}

int main()
{
  int case_num = 1;
  string note, ton;
  while (cin >> note >> ton) {
    cout << "Case " << case_num++ << ": ";
    string other = other_note(note);
    if (other != "") {
      cout << other << ' ' << ton << endl;
    } else {
      cout << "UNIQUE" << endl;
    }
  }
  return 0;
}
