// See Treblecross:
//
// Winning ways for your mathematical plays, v1, 2nd ed. p.94
//
// Pretend that there is one extra square past each boundary.
//
// If we put an X somewhere, then the next move cannot be next to it
// (or the next move automatically loses).  So each move really takes
// out a section of 3 squares (possibly including the extra ones past
// the boundary).  If we consider the segments of empty squares as nim
// heaps, then each move reduces the size of the heap by 3, and may split
// the heap into two smaller ones.  So we just need to compute the nim values
// for all possible single heaps, and use the mex rule to figure out the
// rest.

#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

int nimber[10005];

void init()
{
  fill(nimber, nimber+3, 0);
  for (int n = 3; n <= 10004; n++) {
    int vals[10005];
    int num_vals = 0;

    vals[num_vals++] = nimber[n-3];
      
    for (int k = 1; k <= n-3-k; k++) {
      int index = nimber[k] ^ nimber[n-3-k];
      vals[num_vals++] = index;
    }
    sort(vals, vals+num_vals);
    int prev = -1;
    bool found = false;
    for (int i = 0; i < num_vals; i++) {
      if (vals[i] > prev+1) {
	nimber[n] = prev+1;
	found = true;
	break;
      }
      prev = vals[i];
    }
    if (!found) {
      nimber[n] = prev+1;
    }
  }
}
  
int main(void)
{
  init();
  
  int n;
  string line;
  line.reserve(10000);
  while (cin >> n && n > 0) {
    cin >> line;

    // check to see if there is already a winning move
    bool win = false;
    for (int i = 0; i < n-2; i++) {
      int count = (line[i] == 'X') + (line[i+1] == 'X') + (line[i+2] == 'X');
      if (count == 2) {
	win = true;
      }
    }
    if (win) {
      cout << "S" << endl;
      continue;
    }

    int value = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
      if (line[i] == '.') {
	count++;
      } else {
	if (count) {
	  if (count != i) {
	    // doesn't start from left border
	    assert(count >= 2);
	    count -= 2;
	  }
	    
	  value ^= nimber[count];
	  //	  cout << "count = " << count << endl;
	}
	count = 0;
      }
    }
    if (count) {
      // ends at right border
      if (count == n) {
	// also starts at left border
	count += 2;
      }
      value ^= nimber[count];
      //      cout << "count = " << count << endl;
    }

    if (value) {
      cout << "S" << endl;
    } else {
      cout << "N" << endl;
    }

  }
  return 0;
}
