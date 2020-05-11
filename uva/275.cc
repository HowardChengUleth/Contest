#include <iostream>
#include <map>
#include <string>

using namespace std;

void print_decimals(string decimals)
{
  while (decimals.length() > 50) {
    cout << decimals.substr(0, 50) << endl;
    decimals.erase(0, 50);
  }
  cout << decimals << endl;
}

void solve(int N, int D)
{
  map<int,int> dividend;
  int pos = 0;
  string decimals = ".";

  N = (N % D)*10;
  do {
    dividend[N] = pos;
    char next = (char)(N/D) + '0';
    decimals += next;
    N = (N % D)*10;
    pos++;
  } while (dividend.find(N) == dividend.end() && N != 0);

  if (N == 0) {
    print_decimals(decimals);
    cout << "This expansion terminates." << endl;
  } else {
    int cycle_len = pos - dividend[N];
    print_decimals(decimals);
    cout << "The last " << cycle_len << " digits repeat forever." << endl;
  }

}

int main(void)
{
  int N, D;

  while (cin >> N >> D && (N || D)) {
    solve(N, D);
    cout << endl;
  }
  return 0;
}
