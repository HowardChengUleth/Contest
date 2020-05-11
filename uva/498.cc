/* @JUDGE_ID: 1102NT 498 C++ "" */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int eval(const vector<int> &p, int x)
{
  int ans = 0;
  for (unsigned int i = 0; i < p.size(); i++) {
    ans *= x;
    ans += p[i];
  }
  return ans;
}

int main(void)
{
  string line;

  while (getline(cin, line)) {
    istringstream ss1(line);
    vector<int> p;
    int x;

    while (ss1 >> x) {
      p.push_back(x);
    }

    getline(cin, line);
    istringstream ss2(line);
    bool first = true;
    while (ss2 >> x) {
      if (first) {
	first = false;
      } else {
	cout << ' ';
      }
      cout << eval(p, x);
    }
    cout << endl;
  }
  
  return 0;
}
