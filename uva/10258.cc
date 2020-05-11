#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

struct Team {
  int id, correct, penalty;
  bool solved[10];
  int incorrect[10];
  bool submitted;

  Team() {
    for (int i = 1; i <= 9; i++) {
      solved[i] = false;
      incorrect[i] = 0;
    }
    correct = penalty = 0;
    submitted = false;
  }    
  
  bool operator<(const Team &t) const {
    if (submitted != t.submitted) return submitted;
    if (correct != t.correct) return correct > t.correct;
    if (penalty != t.penalty) return penalty < t.penalty;
    return id < t.id;
  }
};

ostream &operator<<(ostream &os, const Team &t)
{
  return os << t.id << ' ' << t.correct << ' ' << t.penalty;
}

void do_case(void)
{
  string s;
  Team team[101];

  for (int i = 1; i <= 100; i++) {
    team[i].id = i;
  }

  while (getline(cin, s) && s.length() > 0) {
    istringstream is(s);
    int c, p, t;
    char L;
    is >> c >> p >> t >> L;
    team[c].submitted = true;
    if (L == 'C' && !team[c].solved[p]) {
      team[c].solved[p] = true;
      team[c].correct++;
      team[c].penalty += t + 20*team[c].incorrect[p];
    } else if (L == 'I' && !team[c].solved[p]) {
      team[c].incorrect[p]++;
    }
  }

  sort(team, team+101);
  for (int i = 0; i < 101 && team[i].submitted; i++) {
    cout << team[i] << endl;
  }
  
}

int main(void)
{
  int cases;

  cin >> cases;
  cin.ignore();
  cin.ignore();
  while (cases-- > 0) {
    do_case();
    if (cases) {
      cout << endl;
    }
  }
  return 0;
}
