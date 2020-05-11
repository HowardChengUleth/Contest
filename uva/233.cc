#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

struct Package {
  int cat_no;
  int price;
  int howmany[4];

  bool operator<(const Package &p) const
  {
    return cat_no < p.cat_no;
  }
};

istream &operator>>(istream &is, Package &p)
{
  string line;
  if (!getline(is, line)) {
    return is;
  }
  istringstream iss(line);
  iss >> p.cat_no;
  double temp;
  iss >> temp;
  p.price = (int)floor(temp * 100 + 0.5);

  for (int i = 0; i < 4; i++) {
    p.howmany[i] = 0;
  }
  
  char c;
  int num;
  while (iss >> c >> num) {
    p.howmany[c - 'a'] = num;
  }
  return is;
}

struct Request 
{
  int howmany[4];

  bool operator<(const Request &r) const
  {
    return lexicographical_compare(howmany, howmany+4, r.howmany, r.howmany+4);
  }
};

istream &operator>>(istream &is, Request &r)
{
  fill(r.howmany, r.howmany+4, 0);
  string line;
  getline(is, line);
  istringstream iss(line);
  char c;
  int num;
  while (iss >> c >> num) {
    r.howmany[c - 'a'] += num;
  }
  return is;
}

map<Request, int> cheapest;
map<Request, int> which;

int compute(int n, const Package package[], const Request &r)
{
  // see if we are done
  bool is_zero = true;
  for (int i = 0; i < 4; i++) {
    if (r.howmany[i]) is_zero = false;
  }
  if (is_zero) {
    return 0;
  }

  // see if we have computed this before
  map<Request, int>::const_iterator it = cheapest.find(r);
  if (it != cheapest.end()) {
    return it->second;
  }

  int best = -1;
  int best_p;
  
  // now try all possible packages
  for (int p = 0; p < n; p++) {
    Request r2;

    bool useable = false;
    for (int i = 0; i < 4; i++) {
      useable |= (r.howmany[i] > 0 && package[p].howmany[i]);
      r2.howmany[i] = max(0, r.howmany[i] - package[p].howmany[i]);
    }

    if (!useable) continue;
    int val = compute(n, package, r2);
    if (val == -1) continue;
    int temp = package[p].price + val;
    if (best == -1 || temp < best) {
      best = temp;
      best_p = p;
    }
  }

  cheapest[r] = best;
  which[r] = best_p;
  return best;
}

void trace(int number[], const Package package[], const Request &r)
{
  // see if we are done
  bool is_zero = true;
  for (int i = 0; i < 4; i++) {
    if (r.howmany[i]) is_zero = false;
  }
  if (is_zero) {
    return;
  }

  int p = which[r];
  number[p]++;
  Request r2;
  for (int i = 0; i < 4; i++) {
    r2.howmany[i] = max(0, r.howmany[i] - package[p].howmany[i]);
  }
  trace(number, package, r2);
}

int main(void)
{
  Package package[50];
  int n;

  while (cin >> n) {
    cheapest.clear();
    cin.ignore(1);
    for (int i = 0; i < n; i++) {
      cin >> package[i];
    }
    sort(package, package+n);
    
    int m;
    cin >> m;
    cin.ignore(1);
    
    for (int i = 0; i < m; i++) {
      Request r;
      cin >> r;
      int val = compute(n, package, r);
      cout << i+1 << ":";
      cout << setw(5) << setfill(' ') << val / 100 << '.'
	   << setw(2) << setfill('0') << val % 100;

      int number[50];
      fill(number, number+n, 0);
      trace(number, package, r);
      for (int i = 0; i < n; i++) {
	if (number[i] == 0) continue;
	cout << ' ' << package[i].cat_no;
	if (number[i] > 1) {
	  cout << '(' << number[i] << ')';
	}
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}

