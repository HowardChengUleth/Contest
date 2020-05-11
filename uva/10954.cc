#include <iostream>
#include <queue>

using namespace std;

int main(void)
{
  int N;

  // every number in the list will be in the cost at the end,
  // so we need to try and keep the list as small as possible
  // by always adding the 2 smallest remaining
  while (cin >> N && N > 0) {
    // use a priority queue to keep track, but we want a min queue
    // so we negate elements
    priority_queue<int> pq;

    for (int i = 0; i < N; i++) {
      int num;
      cin >> num;
      pq.push(-num);
    }

    long long cost = 0;
    for (int i = 0; i < N-1; i++) {
      int x = -pq.top(); pq.pop();
      int y = -pq.top(); pq.pop();
      cost += x+y;
      pq.push(-(x+y));
    }

    cout << cost << endl;
  }

  return 0;
}
