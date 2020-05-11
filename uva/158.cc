#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int days_in_month[2][12] = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int is_leap(int year)
{
  return year % 4 == 0;
}

struct Event {
  int day, month, priority;
  string desc;
  int pos;
  int day_to_event;

  bool operator<(const Event &e) const {
    /*
    if (month != e.month) return month < e.month;
    if (day != e.day) return day < e.day;
    */
    if (day_to_event != e.day_to_event) 
      return day_to_event < e.day_to_event;
    
    if (day_to_event) {
      int imp = priority - (day_to_event - 1);
      int eimp = e.priority - (e.day_to_event - 1);
      
      if (imp != eimp) return imp > eimp;
    }
    return pos < e.pos;
  }
};

ostream &operator<<(ostream &os, const Event &e)
{
  os << setw(3) << e.day;
  os << setw(3) << e.month;
  if (!e.day_to_event) {
    os << " *TODAY* ";
  } else {
    os << " ";
    int i;
    for (i = 0; i < e.priority-(e.day_to_event-1); i++) {
      os << "*";
    }
    for ( ; i < 8; i++) {
      os << " ";
    }
  }
  os << e.desc;
  return os;
}

istream &operator>>(istream &is, Event &e)
{
  is >> e.day >> e.month >> e.priority;
  while (isspace(is.peek())) {
    is.ignore(1);
  }
  getline(is, e.desc);
  return is;
}

void process(vector<Event> &events, int d, int m, int y)
{
  vector<Event> reminder;

  for (unsigned int i = 0; i < events.size(); i++) {
    bool added = false;
    int dd = d, mm = m, yy = y;

    if (events[i].day == d && events[i].month == m) {
      events[i].day_to_event = 0;
      reminder.push_back(events[i]);
      added = true;
    }

    for (int j = 0; j < events[i].priority && !added; j++) {
      dd++;
      if (dd > days_in_month[is_leap(yy)][mm-1]) {
	dd = 1;
	mm++;
	if (mm > 12) {
	  mm = 1;
	  yy++;
	}
      }
      if (events[i].day == dd && events[i].month == mm) {
	events[i].day_to_event = j+1;
	reminder.push_back(events[i]);
	added = true;
      }
    }
  }
  sort(reminder.begin(), reminder.end());
  cout << "Today is:" << setw(3) << d << setw(3) << m << endl;
  for (unsigned int i = 0; i < reminder.size(); i++) {
    cout << reminder[i] << endl;
  }
}

int main(void)
{
  int year;
  string line;
  vector<Event> events;
  bool first_block = true;
  
  cin >> year;

  char ch;
  while (cin >> ch && ch != '#') {
    if (ch == 'A') {
      Event e;
      cin >> e;
      e.pos = events.size();
      events.push_back(e);
    } else if (ch == 'D') {
      int D, M;
      if (!first_block) {
	cout << endl;
      }
      first_block = false;
      cin >> D >> M;
      process(events, D, M, year);
    }
  }
  return 0;
}
