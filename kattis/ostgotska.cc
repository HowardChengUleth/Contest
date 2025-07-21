#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n = 0, ae = 0;
  string word;

  while (cin >> word) {
    n++;
    if (word.find("ae") != string::npos) {
      ae++;
    }
  }

  if (ae*100 >= 40 * n) {
    cout << "dae ae ju traeligt va" << endl;
  } else {
    cout << "haer talar vi rikssvenska" << endl;
  }


  return 0;
}
