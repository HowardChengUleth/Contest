#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>
#include <cassert>

using namespace std;

class Team
{
private:
  string name;
  int wins, losses, ties;
  int goals_for, goals_against;

  int points() const {
    return 3*wins + ties;
  }

  int played() const {
    return wins + losses + ties;
  }

  int goals_diff() const {
    return goals_for - goals_against;
  }

public:
  Team(const string &n = "")
    : name(n), wins(0), losses(0), ties(0), goals_for(0), goals_against(0)
  {
  }
  
  void play(int myscore, int otherscore)
  {
    goals_for += myscore;
    goals_against += otherscore;
    if (myscore > otherscore) {
      wins++;
    } else if (myscore == otherscore) {
      ties++;
    } else {
      losses++;
    }
  }

  const string &getName() const
  {
    return name;
  }

  bool operator<(const Team &t) const
  {
    if (points() != t.points()) {
      return points() > t.points();
    }
    if (wins != t.wins) {
      return wins > t.wins;
    }
    if (goals_diff() != t.goals_diff()) {
      return goals_diff() > t.goals_diff();
    }
    if (goals_for != t.goals_for) {
      return goals_for > t.goals_for;
    }
    if (played() != t.played()) {
      return played() < t.played();
    }
    string name1 = name, name2 = t.name;
    for (unsigned int i = 0; i < name1.length(); i++) {
      name1[i] = tolower(name1[i]);
    }
    for (unsigned int i = 0; i < name2.length(); i++) {
      name2[i] = tolower(name2[i]);
    }

    return name1 < name2;
  }

  friend ostream &operator<<(ostream &os, const Team &t) 
  {
    os << t.name << " "
       << t.points() << "p, "
       << t.played() << "g "
       << "(" << t.wins << "-" << t.ties << "-" << t.losses << "), "
       << t.goals_diff() << "gd "
       << "(" << t.goals_for << "-" << t.goals_against << ")";
    return os;
  }
};

class Tournament
{
private:
  string name;
  int T;
  Team team[30];

public:
  Tournament() 
    : T(0)
  {
  }
  
  void parse_result(string result)
  {
    string team1, team2;
    int index1, index2;
    int score1, score2;

    index1 = index2 = -1;

    int index = result.find('#');
    team1 = result.substr(0, index);
    result.erase(0, index+1);
    for (int i = 0; i < T; i++) {
      if (team[i].getName() == team1) {
	index1 = i;
      }
    }

    index = result.find('#');
    team2 = result.substr(index+1, result.length()-index);
    result.erase(index, result.length()-index+1);
    for (int i = 0; i < T; i++) {
      if (team[i].getName() == team2) {
	index2 = i;
      }
    }

    assert(index1 >= 0 && index2 >= 0 && index1 != index2);
    
    index = result.find('@');
    result[index] = ' ';
    
    istringstream is(result);
    is >> score1 >> score2;

    team[index1].play(score1, score2);
    team[index2].play(score2, score1);
    

  }

  void rank(void)
  {
    sort(team, team+T);
  }

  friend ostream &operator<<(ostream &os, const Tournament &t)
  {
    os << t.name << endl;
    for (int i = 1; i <= t.T; i++) {
      os << i << ") " << t.team[i-1] << endl;
    }
    return os;
  }

  friend istream &operator>>(istream &is, Tournament &t)
  {
    getline(is, t.name);
    is >> t.T;
    is.ignore(100, '\n');
    for (int i = 0; i < t.T; i++) {
      string tname;
      getline(is, tname);
      t.team[i] = Team(tname);
    }
    int matches;
    is >> matches;
    is.ignore(100, '\n');
    while (matches-- > 0) {
      string result;
      getline(is, result);
      t.parse_result(result);
    }

    return is;
  }
};

int main(void)
{
  int N;

  cin >> N;
  cin.ignore(100, '\n');
  while (N-- > 0) {
    Tournament t;
    cin >> t;
    t.rank();
    cout << t;
    if (N) {
      cout << endl;
    }
  }
  return 0;
}
