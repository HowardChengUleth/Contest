#include <bits/stdc++.h>

using namespace std;

long long read_real()
{
  long long x, y = 0;
  string y_str;
  char dot;

  cin >> x >> dot >> y_str;
  while (y_str.length() < 7) {
    y_str += '0';
  }
  y = stoll(y_str);
  
  // multiply by 10^8 because we may have to div 2
  return x * 100000000 + y * 10;   
}

int nx, ny;
long long w;

bool check(int n, long long M)
{
  M *= 100000000;
  long long pos[1000];
  for (int i = 0; i < n; i++) {
    pos[i] = read_real();
  }
  sort(pos, pos+n);

  // first or last one bad
  if (pos[0] > w/2 || pos[n-1] + w/2 < M) {
    return false;
  }
  for (int i = 1; i < n; i++) {
    // gap is too big
    if (pos[i] - pos[i-1] > w) {
      return false;
    }
  }

  return true;
}

bool solve()
{
  cin >> nx >> ny;
  w = read_real();

  if (nx == 0 && ny == 0 && w == 0) {
    return false;
  }

  bool good = check(nx, 75);
  good = check(ny, 100) && good;   // order matters!

  if (good) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
