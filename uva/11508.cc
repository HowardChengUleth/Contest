#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

bool read_case(int A[], int &n)
{
  string line;
  getline(cin, line);
  if (line == "0") {
    return false;
  }

  istringstream is(line);
  n = 0;
  while (is >> A[n])
    n++;

  return true;
}

bool valid(int A[], int n, int P[])
{
  fill(P, P+n, -1);

  for (int i = 0; i < n; i++) {
    if (A[i] >= n) {
      return false;
    }
    if (P[A[i]] < 0) {
      P[A[i]] = A[i];
      A[i] = -1;
    }
  }

  int j = 0;
  for (int i = 0; i < n; i++) {
    if (A[i] < 0) continue;
    while (P[j] >= 0)
      j++;
    P[j] = A[i];
  }
  return true;
}

int main(void)
{
  int A[10000], n, P[10000];

  while (read_case(A, n)) {
    if (valid(A, n, P)) {
      cout << P[0];
      for (int i = 1; i < n; i++) {
	cout << " " << P[i];
      }
      cout << endl;
    } else {
      cout << "Message hacked by the Martians!!!" << endl;
    }
  }

  return 0;
}
