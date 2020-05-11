#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Proposal
{
  string name;
  int num_met;
  double price;

  Proposal(const string n = "", int met = 0, double p = 0)
    : name(n), num_met(met), price(p) { }

  bool operator<(const Proposal &p) const
  {
    if (num_met != p.num_met) {
      return num_met < p.num_met;
    } else {
      return price > p.price;
    }
  }
};

int main(void)
{
  int n, p;
  Proposal prop[1000];
  int k = 0;

  while (cin >> n >> p && (n || p)) {
    string s;
    getline(cin, s);
    for (int i = 0; i < n; i++) {
      getline(cin, s);
    }

    for (int i = 0; i < p; i++) {
      getline(cin, s);
      double d;
      int r;
      cin >> d >> r;
      prop[i] = Proposal(s, r, d);
      getline(cin, s);
      while (r-- > 0) {
	getline(cin, s);
      }
    }

    if (k) {
      cout << endl;
    }
    cout << "RFP #" << ++k << endl;
    cout << max_element(prop, prop+n)->name << endl;
  }

  return 0;
}
