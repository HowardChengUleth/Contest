/*
 * Euclidean Algorithm
 *
 * Author: Howard Cheng
 *
 * Given two integers, return their gcd.
 *
 */

#include <iostream>
#include <cassert>

using namespace std;

int gcd(int a, int b)
{
  int r;

  /* unnecessary if a, b >= 0 */
  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  assert(a >= 0);
  return a;
}

#include <sstream>

int main(void)
{
  int N;
  cin >> N;
  cin.ignore(1);
  while (N--) {
    string line;
    getline(cin, line);
    istringstream iss(line);

    int M = 0;
    int A[101];
    while (iss >> A[M]) {
      M++;
    }
    int ans = 0;
    for (int i = 0; i < M; i++) {
      for (int j = i+1; j < M; j++) {
	int g = gcd(A[i], A[j]);
	if (g > ans) ans = g;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
