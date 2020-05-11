/* @JUDGE_ID: 1102NT 496 C++ "" */

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

int read_case(set<int>& A, set<int>& B)
{
  A.clear();
  B.clear();

  string line;
  if (!getline(cin, line)) {
    return 0;
  }
  istringstream s1(line);
  int x;
  while (s1 >> x) {
    A.insert(x);
  }

  getline(cin, line);
  istringstream s2(line);
  while (s2 >> x) {
    B.insert(x);
  }
  return 1;
}

void solve_case(const set<int>& A, const set<int>& B)
{
  bool AsubsetB, BsubsetA, common;

  AsubsetB = BsubsetA = true;
  common = false;
  for (set<int>::iterator p = A.begin(); p != A.end(); p++) {
    if (B.find(*p) == B.end()) {
      AsubsetB = false;
    } else {
      common = true;
    }
  }

  for (set<int>::iterator p = B.begin(); p != B.end(); p++) {
    if (A.find(*p) == A.end()) {
      BsubsetA = false;
    } else {
      common = true;
    }
  }

  if (AsubsetB && BsubsetA) {
    cout << "A equals B" << endl;
  } else if (AsubsetB) {
    cout << "A is a proper subset of B" << endl;
  } else if (BsubsetA) {
    cout << "B is a proper subset of A" << endl;
  } else if (!common) {
    cout << "A and B are disjoint" << endl;
  } else {
    cout << "I'm confused!" << endl;
  }
    
}

int main(void)
{
  set<int> A, B;

  while (read_case(A, B)) {
    solve_case(A, B);
  }
  return 0;
}
