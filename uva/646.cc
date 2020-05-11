#include <iostream>
#include <algorithm>

using namespace std;

bool same[256][256];
string table[12];

int spaces[3];

void set(int i, int j, bool val)
{
  same[i][j] = same[j][i] = val;
}

bool read_case(void)
{
  for (int i = 'A'; i <= 'P'; i++) {
    fill(same[i]+'A', same[i]+'P'+1, false);
  }
  
  for (int k = 0; k < 12; k++) {
    if (!(cin >> table[k])) {
      return false;
    }

    if (k < 3) {
      spaces[k] = 0;
      while (cin.peek() == ' ') {
	cin.ignore(1);
	spaces[k]++;
      }
    }

    for (int i = 0; i < 4; i++) {
      for (int j = i+1; j < 4; j++) {
	set(table[k][i], table[k][j], true);
      }
    }
  }

  return true;
}

bool find(char remaining[], int start)
{
  if (start == 32) {
    int k = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
	if (j) {
	  cout << string(spaces[j-1], ' ');
	}
	cout << table[k++];
      }
      cout << endl;
    }

    k = 0;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 4; j++) {
	if (j) {
	  cout << string(spaces[j-1], ' ');
	}
	cout << remaining[k++];
	cout << remaining[k++];
	cout << remaining[k++];
	cout << remaining[k++];
      }
      cout << endl;
    }
    return true;
  }

  if (start == 0 || start == 16) {
    return find(remaining, start+1);
  }

  int word_index = start % 4;
  for (int i = start; i % 16 != 0; i++) {
    bool good = true;
    for (int k = 1; k <= word_index; k++) {
      good &= !same[remaining[start-k]][remaining[i]];
    }
    if (!good) continue;
					   
    swap(remaining[i], remaining[start]);
    for (int k = 1; k <= word_index; k++) {
      set(remaining[start], remaining[start-k], true);
    }

    if (find(remaining, start+1)) {
      return true;
    }
    
    for (int k = 1; k <= word_index; k++) {
      set(remaining[start], remaining[start-k], false);
    }
    swap(remaining[i], remaining[start]);
  }
  
  return false;
}

void solve_case(void)
{
  char remaining[32];

  for (int i = 0; i < 16; i++) {
    remaining[i] = remaining[i+16] = 'A'+i;
  }

  if (!find(remaining, 0)) {
    cout << "It is not possible to complete this schedule." << endl;
  }
}

int main(void)
{
  bool first = true;
  while (read_case()) {
    if (!first) {
      cout << endl;
    }
    solve_case();
    first = false;
  }
  
  return 0;
}
