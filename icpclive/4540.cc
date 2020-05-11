#include <iostream>

using namespace std;

struct Window {
  int r, c, w, h;

  bool inside(int cr, int cc) const
  {
    return (r <= cr && cr < r+h && c <= cc && cc < c+w);
  }
};

istream &operator>>(istream &is, Window &w)
{
  return is >> w.r >> w.c >> w.w >> w.h;
}

bool do_case(int case_num)
{
  int n;
  cin >> n;
  if (n == 0) {
    return false;
  }

  cout << "Desktop " << case_num << ":" << endl;

  Window win[101];
  for (int i = 1; i <= n; i++) {
    cin >> win[i];
  }

  int m;
  cin >> m;
  while (m-- > 0) {
    int cr, cc;
    cin >> cr >> cc;

    bool found = false;
    for (int i = n; i >= 1; i--) {
      if (win[i].inside(cr, cc)) {
	cout << "window " << i << endl;
	found = true;
	break;
      }
    }
    if (!found) {
      cout << "background" << endl;
    }
  }

  return true;
}

int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  return 0;
}
