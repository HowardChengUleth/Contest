//
// Just do it...
//
#include <iostream>
#include <algorithm>

using namespace std;

void print(int a[32])
{
  for (int i = 0; i < 31; i++) {
    cout << a[i];
  }
}

void do_case(void)
{
  int a[32], b[32], c[32], d[32];
  char ch;
  for (int i = 0; i < 31; i++) {
    cin >> ch;
    a[i] = ch - '0';
  }
  for (int i = 0; i < 31; i++) {
    cin >> ch;
    b[i] = ch - '0';
  }
  
  print(a); cout << ' '; print(b); cout << endl;

  while (true) {
    for (int i = 0; i < 31; i++) {
      c[i] = (a[i] != b[i]);
      d[i] = (a[i] && b[i]);
    }

    print(c); cout << ' ';
    if (d[0]) {
      cout << "overflow" << endl;
      return;
    } else {
      for (int i = 0; i < 30; i++) {
	d[i] = d[i+1];
      }
      d[30] = 0;
      print(d); cout << endl;
    }
    copy(c, c+31, a);
    copy(d, d+31, b);
    if (find(d, d+31, 1) == d+31) {
      return;
    }
  }
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    do_case();
    if (T) cout << endl;
  }
  return 0;
}
