/* @JUDGE_ID: 1102NT 570 C++ "" */

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

const int team = 56;         // player 56 is the "team"

struct Player {
  int number, games, hit, kill, block, dig, err;

  Player() 
  {
    number = games = hit = kill = block = dig = err = 0;
  }

  void clear(int n) 
  {
    number = n;
    games = hit = kill = block = dig = err = 0;
  }
  
  void print()
  {
    double hitp, kpg, bpg, dpg;

    if (games) {
      if (kill + err + hit > 0) {
	hitp = static_cast<double>(kill - err) / (kill + err + hit);
      } else {
	hitp = 0;
      }
      kpg = static_cast<double>(kill)/games;
      bpg = static_cast<double>(block)/games;
      dpg = static_cast<double>(dig)/games;
      

      if (number != team) {
	cout.setf(ios::fixed);  cout.precision(0);
	cout.fill('0');         cout.width(2);
	cout << number << "      ";
      } else {
	cout << "team    ";
      }
      cout.fill(' ');
      cout.setf(ios::fixed);  cout.precision(3);
      if (hitp >= 0.000) {
	cout << "+";
      }
      cout << hitp << "   ";
      cout.width(6);
      cout << kpg << "   ";
      cout.width(6);
      cout << bpg << "   ";
      cout.width(6);
      cout << dpg << endl;
    }
  }
};

Player player[team+1];

void clear_players(void)
{
  for (int i = 0; i <= team; i++) {
    player[i].clear(i);
  }
}

int main(void)
{
  char play;
  int n, p;

  clear_players();
  while (cin >> play) {
    switch (play) {
    case 'C':
      cin >> n;
      for (int i = 0; i < n; i++) {
	cin >> p;
	player[p].games++;
      }
      player[team].games++;
      break;
    case 'H':
      cin >> p;
      player[p].hit++;
      player[team].hit++;
      break;
    case 'K':
      cin >> p;
      player[p].kill++;
      player[team].kill++;
      break;
    case 'E':
      cin >> p;
      player[p].err++;
      player[team].err++;
      break;
    case 'B':
      cin >> p;
      player[p].block++;
      player[team].block++;
      break;
    case 'D':
      cin >> p;
      player[p].dig++;
      player[team].dig++;
      break;
    case 'R':
      cout << "Player  Hit Pct    KPG      BPG      DPG" << endl;
      cout << "-----------------------------------------" << endl;

      for (int i = 0; i <= team; i++) {
	player[i].print();
      }
      cout << endl;
      clear_players();
      break;
      //    default:
      //      assert(0);
    }
  }
  return 0;
}

