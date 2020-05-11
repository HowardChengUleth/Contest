/* @JUDGE_ID: 1102NT 10107 C++ "" */

#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

class mid_queue
{
protected:
  int size, mid;
  priority_queue<int> left;
  priority_queue<int, vector<int>, greater<int> > right;

public:
  mid_queue(void)
  {
    size = 0;
  }

  void insert(int x)
  {
    if (size == 0) {
      mid = x;
    } else if (left.size() == right.size()) {
      if (x <= mid) {
	left.push(x);
      } else if (right.size() == 0) {
	left.push(mid);
	mid = x;
      } else if (x <= right.top()) {
	left.push(mid);
	mid = x;
      } else {
	left.push(mid);
	mid = right.top();
	right.pop();
	right.push(x);
      }
    } else {
      if (x >= mid) {
	right.push(x);
      } else if (x >= left.top()) {
	right.push(mid);
	mid = x;
      } else {
	right.push(mid);
	mid = left.top();
	left.pop();
	left.push(x);
      }
    }
    size++;
  }

  int median(void) const
  {
    assert(size > 0);
    if (left.size() == right.size()) return mid;
    return (left.top() + mid) / 2;
  }
};

int main(void)
{
  mid_queue Q;
  int n;

  cin >> n;
  while (!cin.eof()) {
    Q.insert(n);
    cout << Q.median() << endl;
    cin >> n;
  }
  return 0;
}
