#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

bool read_case(int *a)
{			
  bool good = false;

  for (int i = 0; i < 5; i++) {
    cin >> a[i];
    if (a[i] != 0) {
      good = true;
    }
  }

  return good;
}

int eval(int a1, int a2, int op)
{
  switch (op) {
  case 0:
    return a1 + a2;
  case 1:
    return a1 - a2;
  case 2:
    return a1 * a2;
  default:
    assert(0);
    return -1;
  }
}

int eval(int *a, int op1, int op2, int op3, int op4)
{
  return eval(eval(eval(eval(a[0], a[1], op1), a[2], op2), a[3], op3), 
	      a[4], op4);
}

bool possible(int *a)
{
  sort(a, a+5);
  
  do {
    for (int i1 = 0; i1 < 3; i1++) {
      for (int i2 = 0; i2 < 3; i2++) {
	for (int i3 = 0; i3 < 3; i3++) {
	  for (int i4 = 0; i4 < 3; i4++) {
	    if (eval(a, i1, i2, i3, i4) == 23) {
	      return true;
	    }
	  }
	}
      }
    }


  } while (next_permutation(a, a+5));

  return false;
}

int main(void)
{
  int a[5];
  
  while (read_case(a)) {
    cout << (possible(a) ? "Possible" : "Impossible") << endl;
  }
  return 0;
}
