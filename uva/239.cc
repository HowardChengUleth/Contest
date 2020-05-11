#include <iostream>
#include <deque>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

ULL gcd(ULL a, ULL b)
{
  while (b) {
    ULL r = a % b;
    a = b;
    b = r;
  }
  return a;
}

ULL lcm(ULL a, ULL b)
{
  return (a/gcd(a,b))*b;
}

class Clock
{
private:
  int num;
  deque<int> bottom;
  stack<int> minute, five_minute, hour;
  
  void sim_minute(void)
  {
    // pick up a ball from the bottom
    int ball = bottom[0];
    bottom.pop_front();

    // put it on the minute track
    minute.push(ball);
    if (minute.size() < 5) {
      return;
    }

    // overflow to 5 minute track
    five_minute.push(minute.top());
    minute.pop();
    while (!minute.empty()) {
      bottom.push_back(minute.top());
      minute.pop();
    }
    if (five_minute.size() < 12) {
      return;
    }

    // overflow to the hour track
    hour.push(five_minute.top());
    five_minute.pop();
    while (!five_minute.empty()) {
      bottom.push_back(five_minute.top());
      five_minute.pop();
    }
    if (hour.size() < 12) {
      return;
    }

    // overflow the hour track
    ball = hour.top();
    hour.pop();
    while (!hour.empty()) {
      bottom.push_back(hour.top());
      hour.pop();
    }
    bottom.push_back(ball);
  }

  void simulate_12_hours(void) 
  {
    for (int i = 0; i < 12*60; i++) {
      sim_minute();
    }
  }

public:
  Clock(int n)
    : num(n)
  {
    for (int i = 0; i < n; i++) {
      bottom.push_back(i);
    }
  }

  ULL period(void)
  {
    simulate_12_hours();
    
    vector<bool> mark(num);
    fill(mark.begin(), mark.end(), false);

    ULL p = 1;
    for (int i = 0; i < num; i++) {
      if (mark[i]) continue;
      mark[i] = true;
      int cycle_len = 1;
      int k = bottom[i];
      while (k != i) {
	mark[k] = true;
	cycle_len++;
	k = bottom[k];
      }
      p = lcm(p, cycle_len);
    }

    return p;
  }
};

void solve(int n)
{
  Clock clock(n);

  ULL p = clock.period();
  cout << n << " balls cycle after " << (p+1)/2 << " days." << endl;
}

int main(void)
{
  int n;
  while (cin >> n && n) {
    solve(n);
  }

  return 0;
}
