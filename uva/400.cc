#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
  int N;
  string fnames[100];
  unsigned int max_len;
  while (cin >> N) {
    cin.ignore();
    max_len = 0;
    for (int i = 0; i < N; i++) {
      getline(cin, fnames[i]);
      if (max_len < fnames[i].length()) {
	max_len = fnames[i].length();
      }
    }
    
    int num_cols = 61 / (max_len+2);
    if (num_cols < 1) {
      num_cols = 1;
    }

    sort(fnames, fnames+N);

    for (int i = 0; i < 60; i++) {
      cout << "-";
    }
    cout << endl;

    /* figure out how many per column */
    int per_column = N / num_cols;
    if (N % num_cols) {
      per_column++;
    }

    int row = 0, col = 0;
    int pos = 0;
    bool done = false;
    while (!done) {
      if (col != num_cols-1) {
	cout << fnames[pos];
	for (int i = 0; i < max_len+2-fnames[pos].length(); i++) {
	  cout << " ";
	}
      } else {
	cout << fnames[pos];
	for (int i = 0; i < max_len-fnames[pos].length(); i++) {
	  cout << " ";
	}
      }

      if (++col == num_cols ||
	  (col == num_cols-1 && N % per_column &&
	   row >= N % per_column)) {
	row++;
	col = 0;
	pos = row;
	cout << endl;
	if (row >= per_column) {
	  done = 1;
	}
      } else {
	pos += per_column;
      }
    }      
  }
  return 0;
}
