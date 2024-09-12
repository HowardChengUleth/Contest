#include <bits/stdc++.h>

using namespace std;


string ans[3600];

void init()
{
  int hang = 0;
  int mang = 0;
  
  for (int h = 0; h < 12; h++) {
    for (int m = 0; m < 60; m++) {
      int diff = mang - hang;
      if (diff < 0) {
	diff += 3600;
      }

      ostringstream oss;
      oss << setw(2) << setfill('0') << h << ":"
	  << setw(2) << setfill('0') << m;
      ans[diff] = oss.str();

      mang += 3600/60;
      hang += 3600/(12*60);

      mang %= 3600;
      hang %= 3600;
    }
  }
}

int main()
{
  init();

  int ang;
  cin >> ang;
  cout << ans[ang] << endl;

  return 0;
}
