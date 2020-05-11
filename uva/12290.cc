#include <iostream>
#include <algorithm>

using namespace std;

bool clap[80000];

bool has7(int n)
{
  while (n > 0) {
    if (n % 10 == 7) {
      return true;
    }
    n /= 10;
  }
  return false;
}

bool solve()
{
  int n, m, k;
  cin >> n >> m >> k;
  if (!n && !m && !k) return false;

  int delta = 1;

  int person = 1;
  int count = 1;
  while (true) {
    if (person == m && clap[count]) {
      if (--k == 0) {
	cout << count << endl;
	return true;
      }
    }
    count++;
    person += delta;
    if (person == 1) {
      delta = 1;
    } else if (person == n) {
      delta = -1;
    }
  }
}

int main()
{
  for (int n = 0; n < 80000; n++) {
    if (n % 7 == 0) {
      clap[n] = true;
    } else {
      clap[n] = has7(n);
    }
  }

  while (solve())
    ;
  
  return 0;
}
