#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// the notes
string notes[12] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#",
		   "A", "A#", "B" };

// steps from the beginning for the 7 notes of a major scale (note that
// the last one is the same as first one
int steps[7] = { 0, 2, 4, 5, 7, 9, 11 };

bool key_ok(string s, int key)
{
  istringstream ss(s);
  string n;

  while (ss >> n) {
    bool found = false;
    for (int i = 0; i < 7; i++) {
      if (notes[(key+steps[i]) % 12] == n) {
	found = true;
      }
    }
    if (!found) {
      return false;
    }
  }
  return true;
}

int main(void)
{
  string s;

  while (getline(cin, s) && s != "END") {
    bool first = true;
    for (int i = 0; i < 12; i++) {
      if (key_ok(s, i)) {
	if (!first) {
	  cout << ' ';
	}
	cout << notes[i];
	first = false;
      }
    }
    cout << endl;
  }
  return 0;
}
