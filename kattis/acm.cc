#include <bits/stdc++.h>

using namespace std;

// just record and process

int main()
{
  bool solved[256] = {false};
  int sub[256] = {0};
  
  int prob_solved = 0, pen = 0;
  int m;
  while (cin >> m && m > 0) {
    char prob;
    string res;
    cin >> prob >> res;
    if (solved[prob]) continue;
    sub[prob]++;
    if (res == "right") {
      prob_solved++;
      pen += m + 20 * (sub[prob]-1);
      solved[prob] = true;
    }
  }

  cout << prob_solved << ' ' << pen << endl;

  
  return 0;
}
