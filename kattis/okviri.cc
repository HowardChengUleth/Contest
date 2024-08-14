#include <bits/stdc++.h>

using namespace std;


void draw(char ch, int col, vector<string> &output, char mark)
{
  output[0][col+2] = mark;
  output[1][col+1] = output[1][col+3] = mark;
  output[2][col]   = output[2][col+4] = mark;
  output[3][col+1] = output[3][col+3] = mark;
  output[4][col+2] = mark;
  output[2][col+2] = ch;
}

int main()
{
  string s;
  cin >> s;

  int len = s.length()*4+1;

  vector<string> output(5, string(len, '.'));

  for (int i = 0; i < s.length(); i++) {
    if (i % 3 != 2) {
      draw(s[i], i*4, output, '#');
    }
  }
  for (int i = 0; i < s.length(); i++) {
    if (i % 3 == 2) {
      draw(s[i], i*4, output, '*');
    }
  }
  

  for (auto x : output) {
    cout << x << endl;
  }

  return 0;
}
