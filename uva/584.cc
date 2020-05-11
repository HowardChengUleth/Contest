#include <iostream>
#include <string>
#include <sstream>

using namespace std;

char val(char roll[], int i)
{
  if (roll[i] == 'X') {
    return 10;
  } else if (roll[i] == '/') {
    return 10 - val(roll, i-1);
  } else {
    return roll[i] - '0';
  }
}

bool solve()
{
  string line;
  getline(cin, line);
  if (line == "Game Over") {
    return false;
  }

  istringstream iss(line);

  char roll[50];
  int n = 0;
  while (iss >> roll[n]) {
    n++;
  }

  int score = 0;
  int i = 0;
  int frames = 0;
  while (i < n && frames < 10) {
    int frame_score = val(roll, i++);
    if (frame_score == 10) {
      frame_score += val(roll, i) + val(roll, i+1);
    } else {
      frame_score += val(roll, i++);
      if (frame_score >= 10) {
	frame_score = 10 + val(roll, i);
      }
    }
    score += frame_score;
    frames++;
  }
  cout << score << endl;
  return true;
}

int main(void)
{
  while (solve())
    ;

  return 0;
}
