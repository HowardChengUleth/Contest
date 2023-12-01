#include <bits/stdc++.h>

using namespace std;

int calib(const string &s)
{
  const string word[] = {
    "!!!!", "one", "two", "three", "four", "five", "six", "seven",
    "eight", "nine"
  };
  
  int first = -1, last;
  for (int i = 0; i < s.length(); i++) {
    char c = s[i];
    if (isdigit(c)) {
      if (first == -1) {
	first = c - '0';
      }
      last = c - '0';
    } else {
      for (int j = 1; j < 10; j++) {
	if (s.find(word[j], i) == i) {
	  if (first == -1) {
	    first = j;
	  }
	  last = j;
	}
      }
    }
  }
  return first * 10 + last;
}

int main()
{
  string line;
  int total = 0;
  while (getline(cin, line)) {
    total += calib(line);
  }

  cout << total << endl;

  return 0;
}
