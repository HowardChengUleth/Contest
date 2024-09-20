#include <bits/stdc++.h>

using namespace std;

const string mult_name[4] = { "", "single", "double", "triple" };

bool search(int score, int left = 3)
{
  if (!left) {
    return score == 0;
  }
  if (score == 0) {
    return true;
  }
  if (score < 0) {
    return false;
  }
  
  for (int i = 1; i <= 20; i++) {
    for (int mult = 1; mult <= 3; mult++) {
      if (search(score - i*mult, left-1)) {
	cout << mult_name[mult] << ' ' << i << endl;
	return true;
      }
    }
  }

  return false;
}

int main()
{
  int score;
  cin >> score;

  if (!search(score, 3)) {
    cout << "impossible" << endl;
  }


  return 0;
}
