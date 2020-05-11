#include <iostream>
#include <queue>

using namespace std;

long long num[5843];

int main(void)
{
  priority_queue<long long> heap;
  int n, i;
  long long prev = 0;

  i = 0;
  heap.push(-1);

  do {
    long long t = heap.top();
    heap.pop();
    if (t != prev) {
      prev = t;
      num[++i] = -t;
      heap.push(2*t);
      heap.push(3*t);
      heap.push(5*t);
      heap.push(7*t);
    }
  } while (i < 5842);
  
  while (cin >> n && n > 0) {
    cout << "The " << n;
    if (n % 10 == 1 && n % 100 != 11) {
      cout << "st";
    } else if (n % 10 == 2 && n % 100 != 12) {
      cout << "nd";
    } else if (n % 10 == 3 && n % 100 != 13) {
      cout << "rd";
    } else {
      cout << "th";
    }

    cout << " humble number is " << num[n] << "." << endl;
  }
  return 0;
}
