//
// Idea: figured out how to compute f(x), and then integrate
//
// int(f(x), x = 0..1) with enough precision.  Use the simpson's rule in the
// WF code library
//
//

#include <bits/stdc++.h>

using namespace std;

double p;

// -- n is the number of intervals -- IT MUST BE EVEN. O(n)
// -- If K is an upper bound on the 4th derivative of f for all x in [a,b],
//     then the maximum error is ( K*(b-a)^5 ) / ( 180*n^4 )
double integrate(double (*f)(double),
		 double a, double b, int n){
  double ans = f(a) + f(b), h = (b-a)/n;
  for(int i=1;i<n;i++) ans += f(a+i*h) * (i%2 ? 4 : 2);
  return ans * h / 3;
}

double f(double x)
{
  return pow(1 - pow(x,p), 1.0/p);
}

int main()
{
  cin >> p;

  cout << fixed << setprecision(15) << 1-integrate(f, 0, 1, 10'000'000) << endl;

  return 0;
}
