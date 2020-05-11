#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <cmath>

using namespace std;

struct Cat {
  long long pst, gst, hst;

  Cat(double p = 0, double g = 0, double h = 0)
    : pst(p*100+0.5), gst(g*100+0.5), hst(h*100+0.5) { }
};

long long apply(long long rate, long long amount)
{
  return (amount * rate + 5000) / 10000;

}

void do_case(void)
{
  int N, M;
  cin >> N >> M;

  map<string, Cat> category;
  for (int i = 0; i < N; i++) {
    string word;
    double p, g, h;
    char c;
    cin >> word >> p >> c >> g >> c >> h >> c;
    category[word] = Cat(p, g, h);
  }

  long long hst = 0, pgst = 0;
  for (int i = 0; i < M; i++) {
    string word;
    long long dollar, cents;
    char ch;
    cin >> word >> ch >> dollar >> ch >> cents;
    cents += 100*dollar;

    pgst += apply(category[word].pst, cents);
    pgst += apply(category[word].gst, cents);
    hst += apply(category[word].hst, cents); 
  }

  long long diff = hst - pgst;
  if (diff < 0) {
    cout << '-';
    diff = -diff;
  }
  cout << diff / 100 << '.' << setw(2) << setfill('0') << diff % 100 << endl;
}

int main(void)
{
  int cases;
  cin >> cases;
  while (cases-- > 0) {
    do_case();
  }
  return 0;
}
