#include <iostream>
#include <queue>
#include <list>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

void factor(long long n, list<long long> &factors)
{
  if (n == 1) {
    // we won't worry about factors of 1
    return;
  }
  while (n % 2 == 0) {
    factors.push_back(2);
    n /= 2;
  }

  for (long long p = 3; p*p <= n; p += 2) {
    while (n % p == 0) {
      factors.push_back(p);
      n /= p;
    }
  }

  if (n > 1) {
    factors.push_back(n);
  }
}

struct Info
{
  long long a;
  list<long long> factors;

  Info(long long aa, const list<long long> &afactors)
    : a(aa), factors(afactors)
  {
  }
  
  bool operator<(const Info &x) const
  {
    return a > x.a;
  }
};

ostream &operator<<(ostream &os, const Info &info)
{
  os << "a = " << info.a << endl;
  os << "factors =";
  for (list<long long>::const_iterator it = info.factors.begin();
       it != info.factors.end(); ++it) {
    os << ' ' << *it;
  }
  return os << endl;
}


long long heron(long long a, long long b, long long c)
{
  long long sum = a + b + c;
  if (sum % 2 != 0) {
    return -1;
  }
  long long s = sum/2;
  return s * (s-a) * (s-b) * (s-c);
}

bool feasible(long long prod, const Info &info, long long A)
{
  prod /= info.a;
  
  // now look for b and c
  long long prod2 = (long long)ceil(sqrt(prod)) + 1;

  long long a = info.a;
  long long lowerbound = prod2 - (a+1)/2 - 1;
  bool found = false;
  while (lowerbound <= prod2) {
    long long b = lowerbound;
    if (prod % b == 0) {
      long long c = prod / b;
      if (a <= b && b <= c && c < 40001 && a + b > c && heron(a,b,c) == A*A) {
	cout << a << ' ' << b << ' ' << c << endl;
	found = true;
        return true;
      }
    }
    lowerbound++;
  }
  return found;
}

void solve(long long R, long long A)
{
  list<long long> factors;
  
  factor(R, factors);
  factor(A, factors);
  factor(4, factors);
  factors.sort();

  long long prod = 4*A*R;
  long long prod3 = (long long)ceil(pow(prod, 1.0/3.0)) + 1;

  priority_queue<Info> pq;
  pq.push(Info(1, factors));

  long long olda = -1;

  while (!pq.empty()) {
    Info info = pq.top();
    pq.pop();

    if (olda == info.a) continue;
    if (info.a >= 40001) break;
    //    cout << "Info = " << info << endl;

    if (feasible(4*A*R, info, A)) {
      return;
    }
    
    long long preva = -1;
    for (list<long long>::iterator it = info.factors.begin();
	 it != info.factors.end(); ++it) {
      long long newa = info.a * (*it);
      if (newa == preva) continue;
      if (newa > prod3) break;

      long long mult = *it;
      list<long long>::iterator next = it;  ++next;
      info.factors.erase(it);
      Info newinfo(newa, info.factors);
      it = info.factors.insert(next, mult);
      pq.push(newinfo);
      preva = newa;
    }
    olda = info.a;
  }
  cout << "-1 -1 -1" << endl;
}

int main(void)
{
  long long R, A;

  while (cin >> R >> A && (R > 0 && A > 0)) {
    solve(R, A);
  }

  return 0;
}
