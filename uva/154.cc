/* @JUDGE_ID: 1102NT 154 C++ "" */


#include <iostream>
#include <string>
#include <cassert>

using namespace std;

const string color = "roygb";
const string waste = "PGASN";

int n;
int assignment[100][5];

int read_case(void)
{
  string buffer;
  int c, t1, t2;

  getline(cin, buffer);
  if (buffer[0] == '#') {
    return 0;
  }
  n = 0;
  while (buffer[0] != 'e') {
    for (unsigned int i = 0; i < buffer.length(); i++) {
      if (buffer[i] == ',' || buffer[i] == '/') continue;
      t1 = color.find(buffer[i]);
      t2 = waste.find(buffer[i]);
      if (t1 != string::npos) {
	c = t1;
      } else {
	assert(t2 != string::npos);
	assignment[n][c] = t2;
      }
    }
    n++;
    getline(cin, buffer);
  }

  return 1;
}

void do_case(void)
{
  int best = 5*n+1;
  int best_i;

  /* we could have sped things up if we first compute a 5x5 table on how
     many cities have color i for waste j, but what is below is easy... */
  for (int i = 0; i < n; i++) {
    int count = 0;
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < 5; k++) {
	if (assignment[i][k] != assignment[j][k]) {
	  count++;
	}
      }
    }
    if (count < best) {
      best = count;
      best_i = i;
    }
  }
  cout << best_i+1 << endl;
}

int main(void)
{
  while (read_case()) {
    do_case();
  }
  return 0;
}
