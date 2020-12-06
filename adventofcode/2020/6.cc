#include <bits/stdc++.h>

using namespace std;

int main()
{
  int ansA = 0;
  int ansB = 0;
  
  string line;

  while (!cin.eof()) {
    bool seenA[256] = {false};
    int freqB[256] = {0};
    int group = 0;
    while (getline(cin, line) && line != "") {
      for (auto c : line) {
	seenA[c] = true;
	freqB[c]++;
      }
      group++;
    }
    ansA += count(seenA, seenA+256, true);
    if (group > 0) {
      ansB += count(freqB, freqB+256, group);
    }
  }

  cout << "A = " << ansA << endl;
  cout << "B = " << ansB << endl;

  return 0;
}
