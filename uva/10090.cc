/*
 * Extended Euclidean Algorithm
 *
 * Author: Howard Cheng
 *
 * Given two integers, return their gcd and the cofactors to form the
 * gcd as a linear combination.
 *
 * a*s + b*t = gcd(a,b)
 *
 */

#include <iostream>
#include <cmath>

using namespace std;

long long gcd(long long a, long long b, long long &s, long long &t)
{
  long long r, r1, r2, a1, a2, b1, b2, q;

  a1 = b2 = 1;
  a2 = b1 = 0;

  while (b) {
    q = a / b;
    r = a % b;
    r1 = a1 - q*b1;
    r2 = a2 - q*b2;
    a = b;
    a1 = b1;
    a2 = b2;
    b = r;
    b1 = r1;
    b2 = r2;
  }

  s = a1;
  t = a2;
  return a;
}

int main(void)
{
  int n;

  while (cin >> n && n) {
    long long c1, c2, n1, n2;
    cin >> c1 >> n1 >> c2 >> n2;

    long long g, k1, k2;
    g = gcd(n1, n2, k1, k2);
    if (n % g != 0) {
      cout << "failed" << endl;
      continue;
    }

    k1 *= n/g;  k2 *= n/g;

    // general solution is:
    //
    // (k1 + t*n2/g)*n1 + (k2 - t*n1/g)*n2 = n
    //
    // solve for t so that both coefficients are >= 0.
    //
    // we have t1 <= t <= t2
    long long t1 = (long long)ceil((double)(-k1)/(n2/g));
    long long t2 = (long long)floor((double)k2/(n1/g));
    if (t1 > t2) {
      cout << "failed" << endl;
      continue;
    }
    
    // the comparison below actually cannot be == because the answer
    // is supposed to be unique
    long long t = ((n2/g)*c1 >= (n1/g)*c2) ? t1 : t2;
    cout << k1+t*(n2/g) << " " << k2-t*(n1/g) << endl;
    
  }
  return 0;
}
