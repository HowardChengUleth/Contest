#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int row(char c)
{
  if (isdigit(c)) {
    return c - '0' - 1;
  } else {
    return c - 'A' + 9;
  }
}

int main(void)
{
  string s;
  while (cin >> s) {
    int n = s.length();

    long long count[15][15];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	count[i][j] = 0;
      }
    }

    if (s[0] == '?') {
      for (int r = 0; r < n; r++) {
	count[r][0] = 1;
      }
    } else {
      count[row(s[0])][0] = 1;
    }
    
    for (unsigned int j = 1; j < s.length(); j++) {
      if (s[j] == '?') {
	for (int r = 0; r < n; r++) {
	  for (int i = 0; i < n; i++) {
	    if (i != r && i != r-1 && i != r+1) {
	      count[r][j] += count[i][j-1];
	    }
	  }
	}
      } else {
	int r = row(s[j]);
	for (int i = 0; i < n; i++) {
	  if (i != r && i != r-1 && i != r+1) {
	    count[r][j] += count[i][j-1];
	  }
	}
      }

    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
      total += count[i][n-1];
    }
    cout << total << endl;
  }

  return 0;
}
