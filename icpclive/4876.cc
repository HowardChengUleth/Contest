#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int val(char x)
{
  if (isdigit(x)) {
    return x - '0';
  } else {
    return x - 'A' + 10;
  }
}

char tochar(int x)
{
  if (x < 10) {
    return '0' + x;
  } else {
    return x - 10 + 'A';
  }
}

string code(int x)
{
  char s[3] = {0};
  s[0] = tochar(x / 16);
  s[1] = tochar(x % 16);
  return s;
}

void do_case()
{
  int id, B;
  cin >> id >> B;

  int data[5000];
  for (int i = 0; i < B; i++) {
    char c1, c2;
    cin >> c1 >> c2;
    data[i] = val(c1)*16 + val(c2);
  }

  string result;

  int i = 0;
  while (i < B) {
    if (data[i] >= 128) {
      // run
      int len = data[i] - 128 + 3;
      for (int k = 0; k < len; k++) {
	result += code(data[i+1]);
      }
      i += 2;
    } else {
      // non-run
      int len = data[i] + 1;
      i++;
      for (int k = 0; k < len; k++) {
	result += code(data[i++]);
      }
    }
  }
  
  cout << id << ' ' << result.length()/2 << endl;
  while (result.length() > 0) {
    cout << result.substr(0, 80) << endl;
    result.erase(0, 80);
  }
}

int main(void)
{
  int P;
  cin >> P;
  while (P--) {
    do_case();
  }
  return 0;
}
