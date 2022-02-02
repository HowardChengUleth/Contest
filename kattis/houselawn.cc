#include <bits/stdc++.h>

using namespace std;

struct Mower
{
  string name;
  int p, c, t, r;

  void read() {
    string line;
    getline(cin, line);

    auto index = line.find(',');
    name = line.substr(0, index);

    line = line.substr(index+1);
    replace(begin(line), end(line), ',', ' ');
    istringstream iss(line);
    iss >> p >> c >> t >> r;
  }
};

int n = 0;
Mower mower[100];

int main()
{
  int L, m;
  cin >> L >> m;
  cin.ignore(1);
  
  for (int i = 0; i < m; i++) {
    Mower temp;
    temp.read();

    if (temp.c * 10080 * (double)temp.t / (temp.t + temp.r) >= L) {
      mower[n++] = temp;
    }
  }

  if (n == 0) {
    cout << "no such mower" << endl;
  } else {
    int min_p = mower[0].p;
    for (int i = 0; i < n; i++) {
      min_p = min(min_p, mower[i].p);
    }
    for (int i = 0; i < n; i++) {
      if (mower[i].p == min_p) {
	cout << mower[i].name << endl;
      }
    }
  }
  
  return 0;
}
