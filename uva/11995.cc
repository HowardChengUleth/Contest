#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main(void)
{
  int n;
  while (cin >> n) {
    stack<int> s;
    queue<int> q;
    priority_queue<int> pq;
    bool good_s, good_q, good_pq;

    good_s = good_q = good_pq = true;
    
    for (int i = 0; i < n; i++) {
      int type, val;
      cin >> type >> val;
      if (type == 1) {
	if (good_s) {
	  s.push(val);
	}
	if (good_q) {
	  q.push(val);
	}
	if (good_pq) {
	  pq.push(val);
	}
      } else {
	if (good_s &= (!s.empty() && s.top() == val)) {
	  s.pop();
	}
	if (good_q &= (!q.empty() && q.front() == val)) {
	  q.pop();
	}
	if (good_pq &= (!pq.empty() && pq.top() == val)) {
	  pq.pop();
	}
      }
    }

    if (good_s && !good_q && !good_pq) {
      cout << "stack" << endl;
    } else if (!good_s && good_q && !good_pq) {
      cout << "queue" << endl;
    } else if (!good_s && !good_q && good_pq) {
      cout << "priority queue" << endl;
    } else if (good_s || good_q || good_pq) {
      cout << "not sure" << endl;
    } else {
      cout << "impossible" << endl;
    }
  }

  return 0;
}
