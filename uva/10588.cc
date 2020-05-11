/* @JUDGE_ID: 1102NT 10588 C++ "" */

#include <iostream>
#include <queue>

using namespace std;

struct Patient {
  int t;
  unsigned int index;
  vector<int> visits;
  friend istream &operator>>(istream &is, Patient &p);
};

struct Event {
  int t, patient;

  Event(int t, int patient) { this->t = t; this->patient = patient; }
  bool operator<(const Event &e) const {
    if (t != e.t) {
      return t > e.t;
    } else {
      return patient > e.patient;
    }
  }
};

istream &operator>>(istream &is, Patient &p)
{
  int temp, k;
  
  is >> p.t;
  is >> k;
  for (int i = 0; i < k; i++) {
    is >> temp;
    p.visits.push_back(temp-1);
  }
  p.index = 0;
  return is;
}

void solve_case(void)
{
  int n, m;

  cin >> n >> m;

  vector<Patient> patient(n);
  for (int i = 0; i < n; i++) {
    cin >> patient[i];
  }

  int doctors[1000][1000];
  int d_head[1000], d_tail[1000];
  int d_num[1000];
  int waiting = 0;
  
  for (int i = 0; i < m; i++) {
    d_head[i] = d_tail[i] = d_num[i] = 0;
  }

  /* initialize event queue */
  priority_queue<Event> events;
  for (int i = 0; i < n; i++) {
    events.push(Event(patient[i].t, i));
  }

  int curr_t;
  while (!events.empty() || waiting) {
    while ((!events.empty() && curr_t < events.top().t) ||
	   (events.empty() && waiting)) {
      /* if queues are non-empty we better serve them */
      bool found = false;
      for (int i = 0; i < m; i++) {
	if (d_num[i]) {
	  found = true;
	  int p = doctors[i][d_head[i]];
	  d_head[i] = (d_head[i]+1) % 1000;
	  if (--d_num[i] == 0) {
	    waiting--;
	  }

	  patient[p].t = curr_t+1;
	  if (++patient[p].index < patient[p].visits.size()) {
	    events.push(Event(patient[p].t, p));
	  }
	}
      }
      if (found) {
	curr_t++;
      } else {
	curr_t = events.top().t;
      }
    }
    
    /* process everyone at the same time by inserting to the queues */
    Event e = events.top();
    curr_t = e.t;
    while (e.t == curr_t && !events.empty()) {
      events.pop();
      unsigned int &index = patient[e.patient].index;
      int d = patient[e.patient].visits[index];
      doctors[d][d_tail[d]] = e.patient;
      d_tail[d] = (d_tail[d] + 1) % 1000;
      if (d_num[d]++ == 0) {
	waiting++;
      }
      e = events.top();
    }
  }
    
  int latest = patient[0].t;
  for (int i = 1; i < n; i++) {
    if (patient[i].t > latest) {
      latest = patient[i].t;
    }
  }
  cout << latest << endl;
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
