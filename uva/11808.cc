#include <iostream>
#include <algorithm>

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
using namespace std;

// Change this to whatever integer data type will prevent overflow
//   - BigInteger works with this class
typedef long long int dataType;

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
  os << x.num;
  os << '/' << x.denom;
  return os;
}

using namespace std;

#include <string>
#include <sstream>

void eval(string expr, Fraction t, Fraction &pos, Fraction &vel)
{
  // look for top level + 

  int level = 0;
  for (int i = 0; i < expr.length(); i++) {
    if (expr[i] == '(') level++;
    else if (expr[i] == ')') level--;
    else if (expr[i] == '+' && level == 0) {
      Fraction pos2, vel2;
      eval(expr.substr(0, i), t, pos, vel);
      eval(expr.substr(i+1), t, pos2, vel2);
      pos += pos2;
      vel += vel2;
      return;
    }
  }

  // look for top level *
  for (int i = 0; i < expr.length(); i++) {
    if (expr[i] == '(') level++;
    else if (expr[i] == ')') level--;
    else if (expr[i] == '*' && level == 0) {
      Fraction pos1, vel1, pos2, vel2;
      eval(expr.substr(0, i), t, pos1, vel1);
      eval(expr.substr(i+1), t, pos2, vel2);
      pos = pos1 * pos2;
      vel = vel1 * pos2 + vel2 * pos1;
      return;
    }
  }

  if (expr[0] == '(' && expr[expr.length()-1] == ')') {
    eval(expr.substr(1, expr.length()-2), t, pos, vel);
    return;
  }

  if (expr[0] == 't' && expr.length() == 1) {
    pos = t;
    vel = 1;
    return;
  }

  istringstream iss(expr);
  iss >> pos;
  vel = 0;
}

int main()
{
  int id = 1;
  string expr;
  while (cin >> expr) {
    Fraction t;
    cin >> t;
    Fraction pos, vel;
    eval(expr, t, pos, vel);
    cout << "Case #" << id++ << ": " << pos << ' ' << vel << endl;
  }
  return 0;
}
