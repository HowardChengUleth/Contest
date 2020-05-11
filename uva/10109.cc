/* @JUDGE_ID: 1102NT 10109 C++ "" */

//
// The idea is to use Chinese remaindering and then rational reconstruction
// to get the answer.
//

/*
 * Big integer implementation
 *
 * Author: Howard Cheng
 *
 * Each digit in our representation represents LOG_BASE decimal digits
 *
 */

#include <vector>
#include <string>
#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long Digit;
#define BASE 1000000000
#define LOG_BASE 9
#define FMT_STR "%lld"
#define FMT_STR0 "%09lld"

class BigInteger {
private:

  int sign;           // +1 = positive, 0 = zero, -1 = negative
  vector<Digit> mag;  // magnitude
  
  void normalize();

public:
  BigInteger(Digit n = 0);
  BigInteger(const string &s);    // no error checking

  long long toLongLong() const;   // convert to  (assume no overflow)
  string toString() const;        // convert to string


  void clear();  // set to zero

  // comparison
  bool operator<(const BigInteger &a) const;
  bool operator==(const BigInteger &a) const;
  bool isZero() const;

  // arithmetic
  BigInteger &operator+=(const BigInteger &a);
  BigInteger &operator-=(const BigInteger &a);
  BigInteger &operator*=(const BigInteger &a);
  BigInteger &operator*=(Digit a);
  BigInteger &operator<<=(Digit a);
  BigInteger &operator/=(const BigInteger &a);
  BigInteger &operator/=(Digit a);
  BigInteger &operator%=(const BigInteger &a);
  friend Digit operator%(const BigInteger &a, Digit b);
  
  // we have *this = b * q + r
  // r is such that 0 <= r < |b|
  void divide(const BigInteger &b, BigInteger &q, BigInteger &r) const;
  void divide(Digit b, BigInteger &q, Digit &r) const;

  // root = floor(sqrt(a)).  Returns 1 if a is a perfect square, 0 otherwise.
  // assume >= 0
  int sqrt(BigInteger &root) const;
};

BigInteger operator+(const BigInteger &a, const BigInteger &b);
BigInteger operator-(const BigInteger &a, const BigInteger &b);
BigInteger operator*(const BigInteger &a, const BigInteger &b);
BigInteger operator*(const BigInteger &a, Digit b);
BigInteger operator<<(const BigInteger &a, Digit b);
BigInteger operator/(const BigInteger &a, const BigInteger &b);
BigInteger operator/(const BigInteger &a, Digit b);
BigInteger operator%(const BigInteger &a, const BigInteger &b);
Digit operator%(const BigInteger &a, Digit b);

BigInteger power(BigInteger x, Digit y);
istream &operator>>(istream &is, BigInteger &a);
ostream &operator<<(ostream &os, const BigInteger &a);

void BigInteger::normalize()
{
  if (sign == 0) {
    return;
  }
  vector<Digit>::iterator p = mag.end();
  do {
    if (*(--p) != 0) break;
  } while (p != mag.begin());
  if (p == mag.begin() && *p == 0) {
    clear();
  } else {
    mag.erase(++p, mag.end());
  }
}

BigInteger::BigInteger(Digit n)
{
  if (n == 0) {
    sign = 0;
    return;
  }
  if (n < 0) {
    sign = -1;
    n = -n;
  } else {
    sign = 1;
  }
  
  while (n > 0) {
    mag.push_back(n % BASE);
    n /= BASE;
  }
}

BigInteger::BigInteger(const string &s)
{
  int l = 0;
  bool zero = true;

  sign = 1;

  if (s[l] == '-') {
    sign = -1;
    l++;
  }

  int len = s.length() - l;
  int limit = (len % LOG_BASE) ? len/LOG_BASE + 1 : len/LOG_BASE;
  int j = s.length()-1;
  
  for (int i = 0; i < limit; i++) {
    Digit mult = 1, d = 0;
    for (int k = 0; k < LOG_BASE; k++) {
      if (j >= l) {
	d += (s[j] - '0') * mult;
      }
      j--;
      mult *= 10;
    }
    if (d) {
      zero = false;
    }
    mag.push_back(d);
  }
  if (zero) {
    clear();
  }
}

long long BigInteger::toLongLong() const
{
  long long a = 0;
  for (int i = mag.size()-1; i >= 0; i--) {
    a *= BASE;
    a += mag[i];
  }
  return sign * a;
}

string BigInteger::toString() const
{
  char buffer[LOG_BASE+1];
  string s;

  if (isZero()) {
    return "0";
  } else {
    if (sign < 0) {
      s += "-";
    }
    for (int i = mag.size()-1; i >= 0; i--) {
      if (i == (int)(mag.size()-1)) {
	sprintf(buffer, FMT_STR, mag[i]);
      } else {
	sprintf(buffer, FMT_STR0, mag[i]);
      }
      s += buffer;
    }
    return s;
  }
}

void BigInteger::clear()
{
  sign = 0;
  mag.clear();
}

bool BigInteger::operator<(const BigInteger &a) const
{
  if (sign != a.sign) {
    return sign < a.sign;
  } else if (sign == 0) {
    return false;
  } else if (mag.size() < a.mag.size()) {
    return sign > 0;
  } else if (mag.size() > a.mag.size()) {
    return sign < 0;
  } else {
    for (int i = mag.size()-1; i >= 0; i--) {
      if (mag[i] < a.mag[i]) {
	return sign > 0;
      } else if (mag[i] > a.mag[i]) {
	return sign < 0;
      }
    }
    return false;
  }
}

bool BigInteger::operator==(const BigInteger &a) const
{
  return sign == a.sign && mag == a.mag;
}

bool BigInteger::isZero() const
{
  return sign == 0;
}

BigInteger &BigInteger::operator+=(const BigInteger &a)
{
  if (a.sign == 0) {
    return *this;
  } else if (sign == 0) {
    sign = a.sign;
    mag = a.mag;
    return *this;
  } else if (sign < 0 && a.sign > 0) {
    BigInteger b(a);
    sign = 1;
    b -= *this;
    return *this = b;
  } else if (sign > 0 && a.sign < 0) {
    BigInteger b(a);
    b.sign = 1;
    return (*this) -= b;
  } else {
    Digit carry = 0;
    unsigned int limit = max(mag.size(), a.mag.size());
    for (unsigned int i = 0; i < limit; i++) {
      Digit s1 = (i < mag.size()) ? mag[i] : 0;
      Digit s2 = (i < a.mag.size()) ? a.mag[i] : 0;
      Digit sum = s1 + s2 + carry;
      Digit result = (sum < BASE) ? sum : sum - BASE;
      carry = (sum >= BASE);
      if (i < mag.size()) {
	mag[i] = result;
      } else {
	mag.push_back(result);
      }
    }
    if (carry) {
      mag.push_back(carry);
    }
    return *this;
  }
}

BigInteger &BigInteger::operator-=(const BigInteger &a)
{
  if (a.sign == 0) {
    return *this;
  } else if (sign == 0) {
    sign = -a.sign;
    mag = a.mag;
    return *this;
  } else if (sign != a.sign) {
    BigInteger b(a);
    b.sign *= -1;
    return *this += b;
  } else if (sign < 0) {
    BigInteger b(a);
    b.sign *= -1;
    sign *= -1;
    b -= *this;
    return *this = b;
  } else {
    if (*this == a) {
      clear();
      return *this;
    } else if (*this < a) {
      BigInteger b(a);
      b -= *this;
      b.sign *= -1;
      return *this = b;
    } else {
      // we know that *this > a
      unsigned int limit = mag.size();
      Digit borrow = 0;
      for (unsigned int i = 0; i < limit; i++) {
	Digit s1 = mag[i];
	Digit s2 = (i < a.mag.size()) ? a.mag[i] : 0;
	Digit diff = s1 - s2 - borrow;
	mag[i] = (diff >= 0) ? diff : diff + BASE;
	borrow = (diff < 0);
      }
      normalize();
      return *this;
    }
  }
}

BigInteger &BigInteger::operator*=(const BigInteger &a)
{
  BigInteger temp(*this);
  BigInteger c;
  
  if (this == &a) {
    c = a;          // make a copy to prevent clobbering it
  }

  const BigInteger &b = (this == &a) ? c : a;
  
  clear();
  if (b.sign) {
    for (unsigned int i = 0; i < b.mag.size(); i++) {
      if (b.mag[i] != 0) {
	*this += (temp * b.mag[i]);
      }
      temp <<= 1;
    }
    sign *= b.sign;
  }
  return *this;
}

BigInteger &BigInteger::operator*=(Digit a)
{
  if (a <= -BASE || a >= BASE) {
    BigInteger b(a);
    return (*this *= b);
  }

  if (isZero()) {
    return *this;
  } else if (a == 0) {
    clear();
    return *this;
  } else if (a < 0) {
    sign *= -1;
    a = -a;
  }

  Digit carry = 0;
  for (unsigned int i = 0; i < mag.size(); i++) {
    Digit prod = a * mag[i];
    mag[i] = (carry + prod) % BASE;
    carry = (carry + prod) / BASE;
  }
  if (carry) {
    mag.push_back(carry);
  }
  return *this;
}

BigInteger &BigInteger::operator<<=(Digit a)
{
  assert(a >= 0);
  if (sign) {
    while (a-- > 0) {
      mag.insert(mag.begin(), 0);
    }
  }
  return *this;
}

BigInteger &BigInteger::operator/=(const BigInteger &a)
{
  BigInteger temp(*this), r;
  temp.divide(a, *this, r);
  return *this;
}

BigInteger &BigInteger::operator/=(Digit a)
{
  BigInteger temp(*this);
  Digit r;
  temp.divide(a, *this, r);
  return *this;
}
  
BigInteger &BigInteger::operator%=(const BigInteger &a)
{
  BigInteger temp(*this), q;
  temp.divide(a, q, *this);
  return *this;
}

void BigInteger::divide(const BigInteger &b, BigInteger &q, 
			BigInteger &r) const
{
  // reference Knuth v.2 Algorithm D

  assert(!b.isZero());

  if (b.mag.size() == 1) {
    Digit r2;
    divide(b.sign*b.mag[0], q, r2);
    r = r2;
    return;
  } 
    
  r = *this;
  if (r.sign < 0) {
    r.sign = 1;
  }
  q.clear();

  int n = b.mag.size();
  int m = mag.size() - n;
  if (m >= 0) {
    BigInteger v(b);

    q.mag.resize(m+1);
    q.sign = 1;

    // D1: normalize
    Digit d = BASE / (v.mag[n-1] + 1);  // Book is wrong.  See errata on web
    r *= d;
    v *= d;
    while ((int)r.mag.size() < m + n + 1) {
      r.mag.push_back(0);
    }
    
    // loop
    for (int j = m; j >= 0; j--) {
      // D3: calculate q2
      Digit t = r.mag[j+n] * BASE + r.mag[j+n-1];
      Digit q2 = t / v.mag[n-1];
      Digit r2 = t - q2 * v.mag[n-1];
      if (q2 == BASE || q2 * v.mag[n-2] > BASE * r2 + r.mag[j+n-2]) {
	q2--;
	r2 += v.mag[n-1];
	if (r2 < BASE && 
	    (q2 == BASE || q2 * v.mag[n-2] > BASE * r2 + r.mag[j+n-2])) {
	  q2--;
	  r2 += v.mag[n-1];
	}
      }
      
      // D4: multiply and subtract
      Digit carry, borrow, diff;
      carry = borrow = 0;
      for (int i = 0; i <= n; i++) {
	t = q2 * ((i < n) ? v.mag[i] : 0) + carry;
	carry = t / BASE;
	t %= BASE;
	diff = r.mag[j+i] - t - borrow;
	r.mag[j+i] = (diff >= 0 || i == n) ? diff : diff + BASE;
	borrow = (diff < 0);
      }

      // D5: test remainder
      q.mag[j] = q2;
      if (r.mag[n+j] < 0) {
	// D6: add back
	q.mag[j]--;
	carry = 0;
	for (int i = 0; i < n; i++) {
	  t = r.mag[j+i] + v.mag[i] + carry;
	  r.mag[j+i] = (t < BASE) ? t : t - BASE;
	  carry = (t >= BASE);
	}
	r.mag[j+n] += carry;
      }
    }
 
    q.normalize();
    r.normalize();

    // D8: unnormalize
    r /= d;
  }

  // normalize
  if (sign < 0 && b.sign > 0) {
    q.sign *= -1;
    r *= -1;
    if (!r.isZero()) {
      r += b;
      q -= 1;
    }
  } else if (sign > 0 && b.sign < 0) {
    q.sign *= -1;
  } else if (sign < 0 && b.sign < 0 && !r.isZero()) {
    r += b;
    r *= -1;
    q += 1;
  }
}

void BigInteger::divide(Digit b, BigInteger &q, Digit &r) const
{
  if (b <= -BASE || b >= BASE) {
    BigInteger bb(b), rr;
    divide(bb, q, rr);
    r = rr.toLongLong();
    return;
  }

  int bsign = 1;
  if (b < 0) {
    b *= -1;
    bsign = -1;
  }
  q.clear();

  r = 0;
  for (int i = mag.size()-1; i >= 0; i--) {
    Digit t = r * BASE + mag[i];
    if (t / b > 0) {
      q.sign = 1;
    }
    q.mag.insert(q.mag.begin(), t / b);
    r = t - q.mag[0] * b;
  }

  // normalize
  q.normalize();

  if (sign < 0 && bsign > 0) {
    q.sign *= -1;
    r *= -1;
    if (r) {
      r += b;
      q -= 1;
    }
  } else if (sign > 0 && bsign < 0) {
    q.sign *= -1;
  } else if (sign < 0 && bsign < 0 && r) {
    r = b - r;
    q += 1;
  }
}

int BigInteger::sqrt(BigInteger &root) const
{
  assert(sign >= 0);
  root.clear();
  if (sign == 0) {
    return 1;
  }

  // figure out how many digits there are
  BigInteger x, r, t2;
  r.sign = 1;
  int d = mag.size();
  
  int root_d = (d % 2) ? (d+1)/2 : d / 2;

  if (d % 2) {
    r.mag.resize(1);
    r.mag[0] = mag[--d];
  } else {
    r.mag.resize(2);
    r.mag[1] = mag[--d];
    r.mag[0] = mag[--d];
  }

  root.sign = 1;

  // figure out one digit at a time
  for (int k = root_d - 1; k >= 0; k--) {
    // invariant: result is the sqrt (integer part) of the digits processed
    // so far
    
    // look for next digit in result by binary search
    x = root * 2;
    x <<= 1;
    Digit t;

    Digit lo = 0, hi = BASE;
    while (hi - lo > 1) {
      Digit mid = (lo + hi) / 2;
      x.mag[0] = t = mid;
      t2 = x * t;
      if (t2 < r || t2 == r) {
	lo = mid;
      } else {
	hi = mid;
      }
    }
    root <<= 1;
    root.mag[0] = lo;

    // form the next r
    x.mag[0] = t = lo;
    t2 = x * t;
    r -= t2;
    r <<= 2;
    r.mag[1] = mag[--d];
    r.mag[0] = mag[--d];
  }

  return r.isZero();
}

BigInteger operator+(const BigInteger &a, const BigInteger &b)
{
  BigInteger r(a);
  r += b;
  return r;
}

BigInteger operator-(const BigInteger &a, const BigInteger &b)
{
  BigInteger r(a);
  r -= b;
  return r;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b)
{
  BigInteger r(a);
  r *= b;
  return r;
}

BigInteger operator*(const BigInteger &a, Digit b)
{
  BigInteger r(a);
  r *= b;
  return r;
}

BigInteger operator<<(const BigInteger &a, Digit b)
{
  BigInteger r(a);
  r <<= b;
  return r;
}

BigInteger operator/(const BigInteger &a, const BigInteger &b)
{
  BigInteger r(a);
  r /= b;
  return r;
}

BigInteger operator/(const BigInteger &a, Digit b)
{
  BigInteger r(a);
  r /= b;
  return r;
}

BigInteger operator%(const BigInteger &a, const BigInteger &b)
{
  BigInteger r(a);
  r %= b;
  return r;
}
  
Digit operator%(const BigInteger &a, Digit b)
{
  Digit r;
  if (b > 0 && b < BASE) {
    r = 0;
    for (int i = a.mag.size()-1; i >= 0; i--) {
      r = ((r * BASE) + a.mag[i]) % b;
    }
    if (a.sign < 0) {
      r = (b - r) % b;
    }
    return r;
  }
  
  BigInteger q;
  
  a.divide(b, q, r);
  return r;
}

BigInteger power(BigInteger x, int y)
{
  BigInteger result(1), sx(x);
  
  assert(y >= 0);
  while (y > 0) {
    if (y & 0x01) {
      y--;
      result *= sx;
    } else {
      sx *= sx;
      y >>= 1;
    }
  }
  return result;
}

istream &operator>>(istream &is, BigInteger &a)
{
  string s;
  char c;

  is.get(c);
  while (!is.eof() && isspace(c)) {
    is.get(c);
  }
  if (is.eof()) {
    return is;
  }

  if (c == '-') {
    s = "-";
  } else {
    is.unget();
    if (!isdigit(c)) {
      return is;
    }
  }

  is.get(c);
  while (!is.eof() && isdigit(c)) {
    s += c;
    is.get(c);
  }
  if (!is.eof()) {
    is.unget();
  }
  a = s;
  return is;
}

ostream &operator<<(ostream &os, const BigInteger &a)
{
  return (os << a.toString());
}

BigInteger gcd(BigInteger a, BigInteger b)
{
  BigInteger r;
  
  if (a < 0) a *= -1;
  if (b < 0) b *= -1;
  while (!b.isZero()) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

long long gcd(long long a, long long b)
{
  long long r;
  if (a < 0) a *= -1;
  if (b < 0) b *= -1;
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

/////////////////////////////////////////////////////////////////////

long long inv(long long x, long long p)
{
  long long a1 = 1, b1 = 0, b = p;
  while (b) {
    long long q = x / b;
    long long r = x % b, r1 = (a1 - q*b1) % p;
    x = b; a1 = b1;
    b = r; b1 = r1;
  }
  return (a1 < 0) ? a1 + p : a1;
}

BigInteger inv(BigInteger x, BigInteger p)
{
  BigInteger a1 = 1, b1 = 0, b = p;
  while (!b.isZero()) {
    BigInteger q = x / b;
    BigInteger r = x % b, r1 = (a1 - q*b1) % p;
    x = b; a1 = b1;
    b = r; b1 = r1;
  }
  return (a1 < 0) ? a1 + p : a1;
}

class Rational
{
private:
  BigInteger num, denom;

  void reduce() {
    BigInteger g(gcd(num, denom));
    assert(!g.isZero());
    num /= g;
    denom /= g;
    if (denom < 0) {
      num *= -1;
      denom *= -1;
    }
  }

public:
  Rational(Digit n = 0, Digit d = 1) 
    : num(n), denom(d) {
    reduce();
  }

  Rational operator+(const Rational &a) const {
    Rational ans;
    ans.num = num*a.denom + a.num*denom;
    ans.denom = denom * a.denom;
    ans.reduce();
    return ans;
  }

  Rational operator-(const Rational &a) const {
    Rational ans;
    ans.num = num*a.denom - a.num*denom;
    ans.denom = denom * a.denom;
    ans.reduce();
    return ans;
  }

  Rational operator*(const Rational &a) const {
    Rational ans;
    ans.num = num * a.num;
    ans.denom = denom * a.denom;
    ans.reduce();
    return ans;
  }

  Rational operator/(const Rational &a) const {
    Rational ans;
    assert(!a.denom.isZero());
    ans.num = num * a.denom;
    ans.denom = denom * a.num;
    ans.reduce();
    return ans;
  }

  // returns -1 if not possible
  long long operator%(long long p) const {
    long long n = num % p, d = denom % p;
    if (d == 0) {
      return -1;
    }
    long long ans = (n * inv(d, p)) % p;
    if (ans < 0) ans += p;
    return ans;
  }

  bool operator==(const Rational &a) const {
    return num == a.num && denom == a.denom;
  }

  void ratRecon(const BigInteger &g, const BigInteger &M);
  bool ratReconCheck(const BigInteger &g, const BigInteger &M);

  friend istream &operator>>(istream &is, Rational &a);
  friend ostream &operator<<(ostream &os, const Rational &a);
};

void Rational::ratRecon(const BigInteger &g, const BigInteger &M)
{
  BigInteger halfM = (M-1)/2;
  int sign = 1;
  BigInteger sqrtM;
  M.sqrt(sqrtM);

  BigInteger r0, r1, r2, s0, s1, s2, t0, t1, t2, q;

  r0 = M; s0 = 1; t0 = 0;
  r1 = g; s1 = 0; t1 = 1;

  // adjust for negative numbers
  if (halfM < g) {
    r1 = M - g;
    sign = -1;
  }

  while (!(r1 < sqrtM)) {
    r0.divide(r1, q, r2);
    s2 = s0 - q * s1;
    t2 = t0 - q * t1;
    r0 = r1; r1 = r2;
    s0 = s1; s1 = s2;
    t0 = t1; t1 = t2;
  }

  num = r1;
  denom = t1;

  // adjust for negative numbers
  if (sign == -1) {
    num *= -1;
  }
  if (denom < 0) {
    num *= -1;
    denom *= -1;
  }    

  // if the above choice doesn't solve the problem, we need to look for
  // a second solution
  if (!ratReconCheck(g, M)) {
    
    // compute r*, t*
    q = (r0 - sqrtM) / r1 + 1;
    BigInteger rs = r0 - q * r1;
    BigInteger ts = t0 - q * t1;
    num = rs;
    denom = ts;
    if (sign == -1) {
      num *= -1;
    }

    if (denom < 0) {
      num *= -1;
      denom *= -1;
    }
  }
  //  assert(ratReconCheck(g, M));
}

bool Rational::ratReconCheck(const BigInteger &g, const BigInteger &M)
{
  return (num * inv(denom, M)) % M == g && gcd(denom, M) == 1;
}

istream &operator>>(istream &is, Rational &a)
{
  Digit n, d;
  is >> n;
  d = 1;
  if (is.peek() == '/') {
    is.ignore();
    is >> d;
  }
  a = Rational(n,d);
  return is;
}
 
ostream &operator<<(ostream &os, const Rational &a)
{
  os << a.num;
  if (!(a.denom == 1)) {
    os << "/" << a.denom;
  }
  return os;
}

class LRational
{
private:
  long long num, denom;

  void reduce() {
    long long g = gcd(num, denom);
    num /= g;
    denom /= g;
    if (denom < 0) {
      num *= -1;
      denom *= -1;
    }
  }

public:
  LRational(Digit n = 0, Digit d = 1) 
    : num(n), denom(d) {
    reduce();
  }

  LRational operator+(const LRational &a) const {
    LRational ans;
    ans.num = num*a.denom + a.num*denom;
    ans.denom = denom * a.denom;
    ans.reduce();
    return ans;
  }

  LRational operator-(const LRational &a) const {
    LRational ans;
    ans.num = num*a.denom - a.num*denom;
    ans.denom = denom * a.denom;
    ans.reduce();
    return ans;
  }

  LRational operator*(const LRational &a) const {
    LRational ans;
    ans.num = num * a.num;
    ans.denom = denom * a.denom;
    ans.reduce();
    return ans;
  }

  LRational operator/(const LRational &a) const {
    LRational ans;
    assert(a.denom);
    ans.num = num * a.denom;
    ans.denom = denom * a.num;
    ans.reduce();
    return ans;
  }

  // returns -1 if not possible
  long long operator%(long long p) const {
    long long n = num % p, d = denom % p;
    if (d == 0) {
      return -1;
    }
    long long ans = (n * inv(d, p)) % p;
    if (ans < 0) ans += p;
    return ans;
  }

  bool operator==(const LRational &a) const {
    return num == a.num && denom == a.denom;
  }

  friend istream &operator>>(istream &is, LRational &a);
  friend ostream &operator<<(ostream &os, const LRational &a);
};

istream &operator>>(istream &is, LRational &a)
{
  long long n, d;
  is >> n;
  d = 1;
  if (is.peek() == '/') {
    is.ignore();
    is >> d;
  }
  a = LRational(n,d);
  return is;
}
 
ostream &operator<<(ostream &os, const LRational &a)
{
  os << a.num;
  if (!(a.denom == 1)) {
    os << "/" << a.denom;
  }
  return os;
}


///////////////////////////////////////////////////////////////////////

const int NUM_PRIMES = 12;
long long primes[NUM_PRIMES] = 
{ 
  2147483399, 2147483423, 2147483477, 2147483489, 2147483497, 2147483543, 
  2147483549, 2147483563, 2147483579, 2147483587, 2147483629, 2147483647 
};

// Only need 5 lucky primes to reconstruct: this gives a modulus of
// at least 2^128, which is needed to get numerator and denominator
// each of size at most 2^64
//
// But this is not quite enough to prove that there are multiple solutions...
// it all depends on how big the determinant can get.  But it is extremely
// unlikely for the numerator and denominator of the determinant to be
// divisible by 5 big primes.
//
// Using NUM_NEEDED = 1 will actually work for the Spanish archive data...
const int NUM_NEEDED = 5;

const int MAX_M = 50;
const int MAX_N = 50;

bool Reduce(LRational A[MAX_M][MAX_N+1], long long B[MAX_M][MAX_N+1],
	    int m, int n, long long p)
{
  for (int i = 0; i < m; i++) {
    for (int j = 0; j <= n; j++) {
      if ((B[i][j] = A[i][j] % p) < 0) {
	return false;
      }
    }
  }
  return true;
}

// returns   = 0 if there is unique solution
//           < 0 if there is no solution
//         k > 0 if there is a solution space of dimension k
int GaussElim(long long A[MAX_M][MAX_N+1], int m, int n, long long p,
	      long long x[MAX_N])
{
  int k_c, k_r, rank;

  rank = 0;
  k_c = 0;    // column to eliminate

  // eliminate each row
  for (k_r = 0; k_r < m && k_c < n; k_r++) {
    // find nonzero pivot
    int pivot;
    do {
      for (pivot = k_r; pivot < m && A[pivot][k_c] == 0; pivot++)
        ;
      if (pivot >= m) {
        k_c++;
      }
    } while (k_c < n && pivot >= m);
    if (pivot < m) {
      // swap rows pivot and k_r
      if (pivot != k_r) {
        for (int j = k_c; j <= n; j++) {
          long long t = A[pivot][j];
          A[pivot][j] = A[k_r][j];
          A[k_r][j] = t;
        }
      }

      // eliminate
      long long t = inv(A[k_r][k_c], p);
      for (int j = k_c; j <= n; j++) {
	//        A[k_r][j] = (A[k_r][j] * t) % p;
        A[k_r][j] *= t;
	A[k_r][j] %= p;
      }

      for (int k = 0; k < m; k++) {
        if (k == k_r || A[k][k_c] == 0) continue;
        long long t = A[k][k_c];
        for (int j = k_c; j <= n; j++) {
          A[k][j] = A[k][j] - (A[k_r][j] * t) % p;
	  if (A[k][j] < 0) A[k][j] += p;
        }
      }

      rank++;
      k_c++;

    } else {
      // everything else is 0
      break;
    }
  }

  for (int i = rank; i < m; i++) {
    if (A[i][n] != 0) {
      // inconsistent system
      return -1;
    }
  }
  
  if (rank == n) {
    // unique solution
    for (int i = 0; i < n; i++) {
      x[i] = A[i][n] % p;
      //      while (x[i] >= p) x[i] -= p;
      if (x[i] < 0) x[i] += p;
    }
    return 0;
  } else {
    return n - rank;
  }
}

BigInteger cra(long long *a, long long *m, long long *gamma)
{
  const int n = NUM_NEEDED;

  // compute coefficients
  long long v[n];
  v[0] = a[0];
  for (int k = 1; k < n; k++) {
    long long temp = v[k-1];
    for (int i = k-2; i >= 0; i--) {
      temp = ((temp * m[i]) % m[k] + v[i]) % m[k];
      if (temp < 0) {
	temp += m[k];
      }
    }
    v[k] = ((a[k] - temp) % m[k] * gamma[k]) % m[k];
    if (v[k] < 0) {
      v[k] += m[k];
    }
  }

  // convert from mixed-radix representation
  BigInteger x(v[n-1]);
  for (int k = n-2; k >= 0; k--) {
    x *= m[k];
    x += v[k];
  }
  return x;
}

int main(void)
{
  LRational A[MAX_M][MAX_N+1];
  long long Ap[MAX_M][MAX_N+1], x[MAX_N], 
    sol[MAX_N][NUM_NEEDED], modulus[NUM_NEEDED];
  int c, m, n, pi;
  bool first = true;

  while (cin >> c && c > 0) {
    if (!first) {
      cout << endl;
    }
    first = false;

    cout << "Solution for Matrix System # " << c << endl;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j <= n; j++) {
	cin >> A[i][j];
      }
    }

    int count = 0;
    int result = MAX_N+1;
    pi = 0;
    while (count < NUM_NEEDED) {
      for (; pi < NUM_PRIMES && !Reduce(A, Ap, m, n, primes[pi]); pi++)
	;
      assert(pi < NUM_PRIMES);
      int r = GaussElim(Ap, m, n, primes[pi], x);
      if (r < 0) {
	result = r;
	break;
      } else if (r > 0) {
	if (result) {
	  if (r < result) {
	    result = r;
	    count = 1;
	  } else if (r == result) {
	    count++;
	  }
	}
      } else {
	if (result) {
	  result = 0;
	  count = 0;
	}
	for (int i = 0; i < n; i++) {
	  sol[i][count] = x[i];
	  assert(0 <= x[i] && x[i] < primes[pi]);
	}
	modulus[count++] = primes[pi];
      }
      pi++;
    }

    if (result < 0) {
      cout << "No Solution." << endl;
    } else if (result > 0) {
      cout << "Infinitely many solutions containing " << result
           << " arbitrary constants." << endl;
    } else {
      BigInteger M;
      
      M = 1;
      for (int i = 0; i < NUM_NEEDED; i++) {
	M *= modulus[i];
      }

      Rational solution[MAX_N];
      // compute inverses
      long long gamma[NUM_NEEDED];
      for (int k = 1; k < NUM_NEEDED; k++) {
	long long prod = modulus[0] % modulus[k];
	for (int i = 1; i < k; i++) {
	  prod = (prod * modulus[i]) % modulus[k];
	}
	gamma[k] = inv(prod, modulus[k]);
      }



      for (int i = 0; i < n; i++) {
	BigInteger X = cra(sol[i], modulus, gamma);
	solution[i].ratRecon(X, M);
	cout << "x[" << i+1 << "] = " << solution[i] << endl;
      }
    }
  }
  return 0;
}
