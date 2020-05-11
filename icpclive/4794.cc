// idea: Dynamic programming.  The states are (subset, width), and the
// question is whether it is possible to split a chocolate bar of the
// specified width, with the subset of people.  The height is not needed
// because it is implied by the total number of pieces in the subset and
// the width.

#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef unsigned int uint;

int n, x, y;
int part[15];
int table[(1 << 15)][101];

bool possible(uint set, int width)
{
  if (table[set][width] != -1) {
    return table[set][width];
  }

  // height is determined
  int total = 0;
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (set & (1UL << i)) {
      total += part[i];
      count++;
    }
  }
  if (total % width != 0) {
    return (table[set][width] = 0);
  }
  if (count == 1) {
    return (table[set][width] = 1);
  }

  table[set][width] = 0;
  
  int height = total / width;

  // now try splitting set into two in all possible way
  for (uint S1 = 1; S1 < set; S1++) {
    if (S1 & ~set) continue;   // not a subset
    uint S2 = set - S1;
    if (S1 > S2) continue;     // symmetric, ignore
    
    int total1 = 0;
    for (int i = 0; i < n; i++) {
      if (S1 & (1UL << i)) {
	total1 += part[i];
      }
    }

    // try splitting vertically
    if (total1 % height == 0) {
      int width1 = total1 / height;
      if (possible(S1, width1) && possible(S2, width-width1)) {
	return (table[set][width] = 1);
      }
    }

    // try splitting horizontally
    if (possible(S1, width) && possible(S2, width)) {
      return (table[set][height] = 1);
    }
  }
  
  return table[set][width];
}

bool do_case(int case_num)
{
  cin >> n >> x >> y;
  if (n == 0) {
    return false;
  }

  for (int i = 0; i < n; i++) {
    cin >> part[i];
  }

  cout << "Case " << case_num << ": ";

  uint whole = (1UL << n) - 1;
  for (uint i = 0; i <= whole; i++) {
    fill(table[i], table[i]+x+1, -1);
  }

  if (accumulate(part, part+n, 0) == x*y && possible(whole, x)) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
  return true;
}

int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;

  return 0;
}
