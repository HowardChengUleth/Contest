#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

const double PI = acos(-1.0);

int a1, b1, t1, a2, b2;
double t;
double foci;      // x coordinate of the right focus (>= 0)

// -- n is the number of intervals -- IT MUST BE EVEN. O(n)
// -- If K is an upper bound on the 4th derivative of f for all x in [a,b],
//     then the maximum error is ( K*(b-a)^5 ) / ( 180*n^4 )
double f(double x)
{
  return b2 * sqrt(1 - x*x / (a2*a2));
}

double integrate(double (*f)(double), double a, double b, int n){
  double ans = f(a) + f(b), h = (b-a)/n;
  for(int i=1;i<n;i++) ans += f(a+i*h) * (i%2 ? 4 : 2);
  return ans * h / 3;
}

double compute_area(double x)
{
  // there is some closed form formula according to maple...but we can use
  // simpson's rule anyway
  //
  // int = -b/(4*a) * (2*sqrt(a*a - x*x)*x + 2*a*a*asin(x/a) - a*a*PI);
  //  double ans = integrate(f, x, a2, 5000);
  double ans = -b2/4.0/a2 * (2*sqrt(a2*a2-x*x)*x + 2*a2*a2*asin(x/a2) - a2*a2*PI);
  ans += (x - foci) * f(x) / 2;
  return ans;
}


bool solve(int id)
{
  int tt;
  cin >> a1 >> b1 >> t1 >> a2 >> b2 >> tt;
  if (a1 + b1 + t1 + a2 + b2 + tt == 0) return false;

  t = tt;
  
  // period of the 2nd planet
  double t2 = sqrt(pow(a2, 3) * pow(t1, 2)/ pow(a1,3));

  // mod out the period
  double q = floor(t / t2);
  t -= q*t2;
  while (t >= t2) t -= t2;   // just in case
  while (t < 0) t += t2;

  // flip it so it is on the top half
  bool flipped = false;
  if (t > t2/2) {
    t = t2 - t;
    flipped = true;
  }
  
  // area swept = total area * portion of period
  double area = PI * a2 * b2 * t / t2;
  foci = sqrt(a2*a2 - b2*b2);

  double lo = -a2, hi = a2;
  while (hi - lo > 1e-8) {
    double mid = (lo + hi) / 2;
    if (compute_area(mid) > area) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  double x = (lo + hi)/2;
  double y = f(x);
  if (flipped) y *= -1;
  
  cout << "Solar System " << id << ": " << fixed << setprecision(3)
       << x << ' ' << y << endl;
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
