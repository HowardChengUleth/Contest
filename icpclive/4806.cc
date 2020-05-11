#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

bool solve()
{
  int N, B;
  cin >> N >> B;
  if (!N && !B) return false;

  int b[100];
  for (int i = 0; i < B; i++) {
    cin >> b[i];
  }

  bool poss[100] = {false};

  for (int i = 0; i < B; i++) {
    for (int j = 0; j < B; j++) {
      poss[abs(b[i]-b[j])] = true;
    }
  }

  if (count(poss, poss+N+1, false) > 0) {
    cout << "N" << endl;
  } else {
    cout << "Y" << endl;
  }

  return true;
}

int main()
{
  while (solve())
    ;
  
  return 0;
}
