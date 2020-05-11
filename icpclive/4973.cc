#include <iostream>

using namespace std;

//
// Fraction implementation
//
// Author: Darcy Best
//
// Does NOT ever check for division by 0.
// Division by 0 will only cause a runtime error if you use the
//   toDouble() function.
//

#include <iostream>
#include <cstdlib>
#include <utility>

using namespace std;
using namespace std::rel_ops;

// Change this to whatever integer data type will prevent overflow
//   - BigInteger works with this class
typedef long long dataType;

class Fraction{
public:
  Fraction(dataType num=0,dataType denom=1);
	
  double toDouble() const;
	
  void reduce();
	
  // Changes the fraction itself.
  void selfReciprocal();
	
  // Returns a new fraction, leaving the original.
  Fraction reciprocal() const;
	
  Fraction& operator+=(const Fraction& x);
  Fraction& operator-=(const Fraction& x);
  Fraction& operator*=(const Fraction& x);
  Fraction& operator/=(const Fraction& x);
	
  bool operator<(const Fraction& x) const;
  bool operator==(const Fraction& x) const;
	
  dataType num,denom;
};

Fraction operator+(const Fraction& x,const Fraction& y);
Fraction operator-(const Fraction& x,const Fraction& y);
Fraction operator*(const Fraction& x,const Fraction& y);
Fraction operator/(const Fraction& x,const Fraction& y);

istream& operator>>(istream& is,Fraction& x);
ostream& operator<<(ostream& os,const Fraction& x);

Fraction::Fraction(dataType n,dataType d){
  if(d < 0){
    num = -n;
    denom = -d;
  } else {
    num = n;
    denom = d;
  }
  reduce();
}

double Fraction::toDouble() const{
  return 1.0*num/denom;
}

// Howard's GCD function with no checks
dataType gcd(dataType a, dataType b)
{
  dataType r;
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

void Fraction::reduce(){
  dataType g = gcd(abs(num),denom);
  num /= g;
  denom /= g;
}

void Fraction::selfReciprocal(){
  swap(num,denom);
  if (denom < 0) {
    num = -num;
    denom = -denom;
  }
}

Fraction Fraction::reciprocal() const{
  return Fraction(denom,num);
}

// Overflow potential in the denominator.
// I've tried to factor out as much as possible before,
//   But be careful.
//
//   (w)/(a*g) + (z)/(b*g)
// = (w*b)/(a*g*b) + (a*z)/(a*g*b)
// = (w*b + a*z)/(a*g*b)
Fraction& Fraction::operator+=(const Fraction& x){
  dataType g = gcd(denom,x.denom);
	
  dataType a = denom / g;
  dataType b = x.denom / g;
	
  num = num * b + x.num * a;
  denom *= b;
	
  reduce();
	
  return (*this);
}

Fraction& Fraction::operator-=(const Fraction& x){
  dataType g = gcd(denom,x.denom);
  dataType a = denom / g;
  dataType b = x.denom / g;
	
  num = num * b - x.num * a;
  denom *= b;
	
  reduce();
  return (*this);
}

Fraction& Fraction::operator*=(const Fraction& x){
  num *= x.num;
  denom *= x.denom;
  reduce();
  return (*this);
}

Fraction& Fraction::operator/=(const Fraction& x){
  num *= x.denom;
  denom *= x.num;
	
  if(denom < 0){
    num = -num;
    denom = -denom;
  }
  reduce();
  return (*this);
}

// Careful with overflow. If it is an issue, you can compare the
// double values, but you SHOULD check for equality BEFORE converting
bool Fraction::operator<(const Fraction& x) const{
  return (num*x.denom) < (x.num*denom);
}

bool Fraction::operator==(const Fraction& x) const{
  return (num == x.num) && (denom == x.denom);
}

Fraction operator+(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a += y;
  return a;
}

Fraction operator-(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a -= y;
  return a;
}

Fraction operator*(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a *= y;
  return a;
}

Fraction operator/(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a /= y;
  return a;
}

// Note that you can read in Fractions of two forms:
// a/b (With any number of space between a,/,b) - The input "points" to
//      the NEXT character after the denom (White space or not)
// c   (Just an integer - The input "points" to the next NON-WHITE SPACE
//      character. Careful when mixing this with getline.)
istream& operator>>(istream& is,Fraction& x){
  is >> x.num;
	
  char ch;
  is >> ch;
  if(ch != '/'){
    is.putback(ch);
    x.denom = 1;
  } else {
    is >> x.denom;
    if(x.denom < 0){
      x.num = -x.num;
      x.denom = -x.denom;
    }
    x.reduce();
  }
	
  return is;
}

// Will output 5 for 5/1 and 0 for 0/1. If you want always
//    fractions, get rid of the if statement
ostream& operator<<(ostream& os,const Fraction& x){
  os << x.num << ' ' << x.denom;
  return os;
}


struct Point {
  int x, y, z;
};

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y >> p.z;
}

int dot(const Point &a, const Point &b)
{
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

Point a, b, c, d;

int sqdist(const Point &a, const Point &b)
{
  int dx = a.x-b.x;
  int dy = a.y-b.y;
  int dz = a.z-b.z;
  return dx*dx + dy*dy + dz*dz;
}

Fraction sqdist(const Fraction &s, const Fraction &t)
{
  Fraction dx, dy, dz;

  dx = t*(b.x - a.x) - s*(d.x - c.x) - (c.x - a.x);
  dy = t*(b.y - a.y) - s*(d.y - c.y) - (c.y - a.y);
  dz = t*(b.z - a.z) - s*(d.z - c.z) - (c.z - a.z);
  return dx*dx + dy*dy + dz*dz;
}

// maple code to generate the formulas
//
// l1 := <Ax,Ay,Az> + t * <Bx-Ax, By-Ay, Bz-Az>;
// l2 := <Cx,Cy,Cz> + s * <Dx-Cx, Dy-Cy, Dz-Cz>;
// v := l1 - l2;
// n := v[1]^2 + v[2]^2 + v[3]^2;

void solve()
{
  cin >> a >> b >> c >> d;

  Fraction best = min(min(sqdist(a,c), sqdist(b,c)),
		      min(sqdist(a,d), sqdist(b,d)));

  // try one end point to the other line
  Fraction zero = 0, one = 1;
  Fraction temp;
  int top, bot;

  // solve(diff(subs(s=0, n), t) = 0, t);
  top = dot(a,a) - dot(a,b) + dot(b,c) - dot(a,c);
  bot = dot(a,a) + dot(b,b) - dot(a,b) * 2;
  if (bot < 0) {
    top = -top;
    bot = -bot;
  }
  if (0 <= top && top <= bot) {
    temp = Fraction(top, bot);
    best = min(best, sqdist(0,temp));
  }
  
  // solve(diff(subs(s=1, n), t) = 0, t);
  top = dot(a,a) - dot(a,b) + dot(b,d) - dot(a,d);
  if (bot < 0) {
    top = -top;
    bot = -bot;
  }
  if (0 <= top && top <= bot) {
    temp = Fraction(top, bot);
    best = min(best, sqdist(1,temp));
  }

  // solve(diff(subs(t=0, n), s) = 0, s);
  top = dot(a,d) - dot(a,c) + dot(c,c) - dot(c,d);
  bot = dot(c,c) + dot(d,d) - dot(c,d) * 2;
  if (bot < 0) {
    top = -top;
    bot = -bot;
  }
  if (0 <= top && top <= bot) {
    temp = Fraction(top, bot);
    best = min(best, sqdist(temp,0));
  }

  // solve(diff(subs(t=1, n), s) = 0, s);
  top = dot(b,d) - dot(b,c) + dot(c,c) - dot(c,d);
  if (bot < 0) {
    top = -top;
    bot = -bot;
  }
  if (0 <= top && top <= bot) {
    temp = Fraction(top, bot);
    best = min(best, sqdist(temp,1));
  }

  // now see what happens for both s and t

  // solns := solve({diff(n, s) = 0, diff(n, t) = 0}, {s, t});
  // eqn1 := collect(diff(n,s), {s,t});
  // eqn2 := collect(diff(n,t), {s,t});
  // cA := coeff(eqn1, s);
  // cB := coeff(eqn1, t);
  // cC := -(eqn1 - cA*s - cB*t);
  // cD := coeff(eqn2, s);
  // cE := coeff(eqn2, t);
  // cF := -(eqn2 - cD*s - cE*t);

  // so we have cA*s + cB*t = cC
  //            cD*s + cE*t = cF
  int cA = sqdist(c, d) * 2;
  int cB = 2*((b.x-a.x)*(c.x-d.x) + (b.y-a.y)*(c.y-d.y) +
		   (b.z-a.z)*(c.z-d.z));
  int cC = -2*((a.x-c.x)*(c.x-d.x) + (a.y-c.y)*(c.y-d.y) +
		    (a.z-c.z)*(c.z-d.z));

  int cD = cB;
  int cE = sqdist(a, b) * 2;
  int cF = -2*((a.x-c.x)*(b.x-a.x) + (a.y-c.y)*(b.y-a.y) +
		    (a.z-c.z)*(b.z-a.z));

  int det = cA*cE - cD*cB;
  if (det != 0) {
    int numerS = cC*cE - cF*cB;
    int numerT = cA*cF - cD*cC;
    if (det < 0) {
      numerS = -numerS;
      numerT = -numerT;
      det = -det;
    }
    if (numerS > 0 && numerT > 0 && numerS < det && numerT < det) {
      Fraction s(numerS, det), t(numerT, det);
      best = min(best, sqdist(s, t));
    }
  }

  cout << best << endl;
}

int main(void)
{
  int Z;
  cin >> Z;
  while (Z--) {
    solve();
  }
  return 0;
}
