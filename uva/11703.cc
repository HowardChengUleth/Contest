#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int x[1000001];
bool init[1000001];

int compute(int i)
{
  if (init[i]) {
    return x[i];
  }
  if (i == 0) {
    init[i] = true;
    return x[i] = 1;
  }

  int index1 = (int)floor(i - sqrt(i));
  int index2 = (int)floor(log(i));
  int index3 = (int)floor(i* sin(i)*sin(i));

  init[i] = true;
  return x[i] = ((compute(index1) + compute(index2) + compute(index3)) 
		 % 1000000);
}

int main(void)
{
  int i;
  while (cin >> i && i != -1) {
    cout << compute(i) << endl;
  }

  return 0;
}
