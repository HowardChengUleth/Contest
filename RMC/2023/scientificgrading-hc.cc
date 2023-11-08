#include <bits/stdc++.h>

using namespace std;

struct Float
{
  // sparse rep digits indexed by power, all nonzero digits in [-9, 9]
  //
  // 0 is empty list
  map<int,int> dig;

  int max_exp() const
  {
    return (dig.size() > 0) ? dig.rbegin()->first : INT_MIN;
  }

  int lead_dig() const
  {
    if (dig.size() == 0)
      return 0;

    return dig.rbegin()->second;
  }

  int sign() const
  {
    if (dig.size() == 0)
      return 0;
    
    return (lead_dig() > 0) ? 1 : -1;
  }

  bool zero() const
  {
    return sign() == 0;
  }
  
  void normalize()
  {
    int hi_exp = max_exp();
    for (auto [e, d] : dig) {
      while (d >= 10) {
	// carry
	d -= 10;
	dig[e] -= 10;
	dig[e+1]++;
      }
      while (d <= -10) {
	// borrow
	d += 10;
	dig[e] += 10;
	dig[e+1]--;
      }
      if (e == hi_exp) break;
    }
    
    for (auto it = dig.begin(); it != dig.end(); ) {
      if (it->second == 0) {
	it = dig.erase(it);
      } else {
	++it;
      }
    }
  }
};

// for debugging
ostream &operator<<(ostream &os, const Float &f)
{
  for (auto [e, d] : f.dig) {
    os << "(" << d << "e" << e << ") ";
  }
  if (f.dig.size() == 0) {
    os << "0";
  }
  return os;
}

istream &operator>>(istream &is, Float &f)
{
  f.dig.clear();

  string s;
  is >> s;

  int sign = (s[0] == '-') ? -1 : 1;
  auto epos = s.find('e');
  int exp = stoi(s.substr(epos+1));
  for (int i = 0; i < epos; i++) {
    if (!isdigit(s[i])) continue;
    int d = s[i] - '0';
    if (d) {
      f.dig[exp] = sign * d;
    }
    exp--;
  }
  f.normalize();
  return is;
}

Float operator-(const Float &x)
{
  Float temp;
  for (auto [e, d] : x.dig) {
    temp.dig[e] = -d;
  }
  temp.normalize();
  return temp;
}

Float operator+(const Float &x, const Float &y)
{
  Float ans = x;
  for (auto [e, d] : y.dig) {
    ans.dig[e] += d;
  }

  ans.normalize();
  return ans;
}

Float operator-(const Float &x, const Float &y)
{
  return x + (-y);
}

Float abs(const Float &x)
{
  if (x.sign() < 0) {
    return -x;
  } else {
    return x;
  }
}

Float abs_error(const Float &expect, const Float &val)
{
  return abs(expect - val);
}

Float operator*(const Float &x, const Float &y)
{
  if (x.sign() == 0) {
    return x;
  }
  if (y.sign() == 0) {
    return y;
  }
  if (x.sign() * y.sign() < 0) {
    return -(abs(x) * abs(y));
  }

  Float ax = abs(x), ay = abs(y);
  Float ans;
  for (auto [xe, xd] : x.dig) {
    for (auto [ye, yd] : y.dig) {
      ans.dig[xe + ye] += xd * yd;
    }
  }

  ans.normalize();
  return ans;
}

bool operator<(const Float &x, const Float &y)
{
  Float diff = x - y;
  return (diff.sign() < 0);
  
  if (x.sign() == 0) {
    return y.sign() > 0;
  }
  if (y.sign() == 0) {
    return x.sign() < 0;
  }

  if (x.sign() < y.sign())
    return true;

  if (x.sign() < 0) {
    return abs(y) < abs(x);
  }

  assert(x.sign() > 0 && y.sign() > 0);
  
  int xexp = x.max_exp();
  int yexp = y.max_exp();
  return (xexp < yexp ||
	  (xexp == yexp && x.lead_dig() < y.lead_dig()));
}

void check(const Float &expect, const Float &ans, const Float &tolerance)
{
  bool good;

  Float aerror = abs_error(expect, ans);
  if (expect.zero()) {
    good = aerror.zero();
  } else {
    good = (aerror < tolerance);
    good &= (aerror < (tolerance * abs(expect)));
  }

  if (good) {
    cout << "Correct" << endl;
  } else {
    cout << "Incorrect" << endl;
  }
}

void check_div(const Float &x, const Float &y, const Float &ans,
	       const Float &tolerance)
{
  bool good = (abs(x - y * ans) < tolerance * abs(y));
  good &= (abs(x - y * ans) < tolerance * abs(x));
  
  if (good) {
    cout << "Correct" << endl;
  } else {
    cout << "Incorrect" << endl;
  }
}

int main()
{
  Float x, y;
  cin >> x >> y;

  Float ans;
  Float tolerance;
  tolerance.dig[-9] = 1;

  cin >> ans;
  check(x+y, ans, tolerance);
  
  cin >> ans;
  check(x-y, ans, tolerance);
  
  cin >> ans;
  check(x*y, ans, tolerance);

  cin >> ans;
  check_div(x, y, ans, tolerance);

  return 0;
}
