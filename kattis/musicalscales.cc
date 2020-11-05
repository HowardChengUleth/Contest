#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  string notes[12] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };
  int offset[7] = { 2, 2, 1, 2, 2, 2, 1 };
  vector<string> scale[12];

  for (int i = 0; i < 12; i++) {
    int index = i;
    scale[i].push_back(notes[index]);
    for (int j = 0; j < 7; j++) {
      index += offset[j];
      index %= 12;
      scale[i].push_back(notes[index]);
    }
  }

  string song[100];
  for (int i = 0; i < n; i++) {
    cin >> song[i];
  }

  int found = 0;
  for (int i = 0; i < 12; i++) {
    bool good = true;
    for (int j = 0; j < n; j++) {
      good &= find(begin(scale[i]), end(scale[i]), song[j]) != end(scale[i]);
    }
    if (good) {
      cout << notes[i] << ' ';
      found++;
    }
  }
  if (!found) {
    cout << "none";
  }
  cout << endl;

  return 0;
}
