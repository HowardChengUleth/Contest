#include <iostream>
#include <algorithm>

using namespace std;

bool solve_case(void)
{
  int k, m;
  cin >> k;  
  if (k == 0) {
    return false;
  }

  cin >> m;
  
  int chosen[100];
  for (int i = 0; i < k; i++) {
    cin >> chosen[i];
  }
  
  bool good = true;
  for (int i = 0; i < m; i++) {
    int c, r;
    cin >> c >> r;

    for (int j = 0; j < c; j++) {
      int course;
      cin >> course;
      if (find(chosen, chosen+k, course) != chosen+k) {
	r--;
      }
    }
    if (r > 0) {
      good = false;
    }
  }

  cout << (good ? "yes" : "no") << endl;
  

  return true;
}

int main(void)
{
  while (solve_case())
    ;
  return 0;
}
