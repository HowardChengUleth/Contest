#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Car
{
  ll arr, fill;
  int side;
  ll left;
};

istream &operator>>(istream &is, Car &car)
{
  char ch;
  is >> car.arr >> car.fill >> ch;
  car.side = (ch == 'L');
  return is;
}

struct Event
{
  ll time;
  int c_index;                 // which car it is
  bool arrive;                 // is it arriving or leaving
  int pump_index, pumpAB;      // where the car is at the pump

  Event(ll t, int index)
    : time{t}, c_index{index}, arrive{true}, pump_index{-1},
      pumpAB{-1}
  { }

  Event(ll t, int index, int p_index, int pAB)
    : time{t}, c_index{index}, arrive{false}, pump_index{p_index}, pumpAB{pAB}
  {}
  
  bool operator<(const Event &e) const
  {
    if (time != e.time) {
      return time > e.time;
    }

    // anyone who is leaving should be given priority
    return (arrive && !e.arrive);
  }
};


vector<Car> car;
const int MAX_P = 100;

// (column, A/B = 0/1, L/R = 0/1)
bool pump[MAX_P][2][2];
queue<int> lineup[MAX_P][2];
priority_queue<Event> event;


int P, N;

bool open_column(int pi, int side)
{
  return !pump[pi][0][side];
}

void serve(int cindex, int pi, int time)
{
  int side = car[cindex].side;
  assert(open_column(pi, side));
  
  int pumpAB = 0;
  if (!pump[pi][1][side]) {
    pumpAB = 1;
  }
  pump[pi][pumpAB][side] = true;
  event.emplace(time + car[cindex].fill,
		cindex, pi, pumpAB);
}

void process_arrive(Event e)
{
  int index = e.c_index;
  int side = car[index].side;

  // look for open column
  for (int i = 0; i < P; i++) {
    if (open_column(i, side)) {
      serve(index, i, car[index].arr);
      return;
    }
  }

  // look for a queue to line up
  int best_q = 0;
  for (int i = 0; i < P; i++) {
    if (lineup[i][side].size() < lineup[best_q][side].size()) {
      best_q = i;
    }
  }
  lineup[best_q][side].push(index);
}

void process_leave(Event e)
{
  int pi = e.pump_index;
  int pAB = e.pumpAB;
  int side = car[e.c_index].side;

  car[e.c_index].left = e.time;
  
  assert(pump[pi][pAB][side]);

  // leave
  pump[pi][pAB][side] = false;
}

void check_queues(ll time)
{
  for (int pi = 0; pi < P; pi++) {
    for (int side = 0; side < 2; side++) {
      while (!lineup[pi][side].empty() &&
	     open_column(pi, side)) {
	serve(lineup[pi][side].front(), pi, time);
	lineup[pi][side].pop();
      }
    }
  }
}

int main()
{
  cin >> P >> N;
  car.resize(N);
  for (auto &c : car) {
    cin >> c;
  }

  ll time = 0;
  for (int i = 0; i < N; i++) {
    event.emplace(car[i].arr, i);
  }

  while (!event.empty()) {
    Event e = event.top();
    event.pop();

    if (e.arrive) {
      process_arrive(e);
    } else {
      // everyone leaving at the same time: make them all leave
      ll time = e.time;
      process_leave(e);
      while (!event.empty() && !event.top().arrive &&
	     event.top().time == time) {
	e = event.top();
	event.pop();
	process_leave(e);
      }
      check_queues(time);
    }
  }

  for (auto c : car) {
    cout << c.left << endl;
  }
    
  return 0;
}
