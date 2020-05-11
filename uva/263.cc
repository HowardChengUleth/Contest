/* @JUDGE_ID: 1102NT 263 C++ "" */

#include <iostream>
#include <set>

using namespace std;

void steps12(int orig, int &desc, int &asc)
{
  int count[10];

  for (int i = 0; i < 10; i++) {
    count[i] = 0;
  }

  while (orig > 0) {
    count[orig % 10]++;
    orig /= 10;
  }
  
  desc = asc = 0;

  for (int i = 9; i >= 0; i--) {
    for (int j = 0; j < count[i]; j++) {
      desc = desc*10 + i;
    }
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < count[i]; j++) {
      asc = asc*10 + i;
    }
  }
}

void solve(int n)
{
  set<int> chain;
  int desc, asc;

  cout << "Original number was " << n << endl;
  chain.insert(n);
  steps12(n, desc, asc);
  n = desc - asc;
  cout << desc << " - " << asc << " = " << n << endl;
  while (chain.find(n) == chain.end()) {
    chain.insert(n);
    steps12(n, desc, asc);
    n = desc - asc;
    cout << desc << " - " << asc << " = " << n << endl;
  }
  cout << "Chain length " << chain.size() << endl;
  cout << endl;
}

int main(void)
{
  int n;

  while (cin >> n && n) {
    solve(n);
  }
  return 0;
}
