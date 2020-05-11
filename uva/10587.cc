/* @JUDGE_ID: 1102NT 10587 C++ "" */

#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Interval {
  int l, r;
};

void solve_case(void)
{
  int n;
  cin >> n;

  vector<Interval> poster(n);
  for (int i = 0; i < n; i++) {
    cin >> poster[i].l >> poster[i].r;
  }

  list<Interval> intervals;
  int count = 0;

  /* process posters backward */
  for (int i = n-1; i >= 0; i--) {
    list<Interval>::iterator p, q, s;
    q = 0;
    for (p = intervals.begin(); p != intervals.end() && 
	   p->r < poster[i].l; p++) {
      q = p;
    }

    if (p == intervals.end()) {
      count++;
      if (q != 0 && q->r+1 == poster[i].l) {
	q->r = poster[i].r;
      } else {
	intervals.insert(p, poster[i]);
      }
    } else {
      if (poster[i].l < p->l || poster[i].r > p->r) {
	count++;
      }

      Interval temp;
      temp.l = (poster[i].l < p->l) ? poster[i].l : p->l;
      for (s = p; s != intervals.end() && s->r < poster[i].r; s++) ;
      if (s == intervals.end() || s->r == poster[i].r ||
	  s->l > poster[i].r + 1) {
	temp.r = poster[i].r;
      } else {
	temp.r = s->r;
      }
      if (q != 0 && q->r+1 == temp.l) {
	q->r = temp.r;
	p = q;
      } else {	
	p = intervals.insert(p, temp);
      }
      

      q = p;
      q++;
      while (p->l <= q->l && q->r <= p->r) {
	intervals.erase(q++);
      }
    }
    /*
    cout << "====================" << endl;
    cout << "After poster " << i+1 << endl << endl;
    for (p = intervals.begin(); p != intervals.end(); p++) {
      cout << p->l << "," << p->r << endl;
    }
    cout << endl;
    */
  }

  cout << count << endl;
}

int main(void)
{
  int c;
  
  cin >> c;
  while (c-- > 0) {
    solve_case();
  }

  return 0;
}
