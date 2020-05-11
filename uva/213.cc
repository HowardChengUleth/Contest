#include <iostream>
#include <string>

using namespace std;

char key[8][128];

int readint(int len)
{
  int ans = 0;
  for (int i = 0; i < len; i++) {
    char c;
    cin >> c;
    ans = 2*ans + c - '0';
  }
  return ans;
}

int main(void)
{
  string head;
  while (getline(cin, head)) {
    int len = 1;
    int index = 0;
    for (unsigned int k = 0; k < head.length(); k++) {
      key[len][index] = head[k];
      index++;
      if (index == (1 << len) - 1) {
	len++;
	index = 0;
      }
    }

    while (len = readint(3)) {
      int code;
      while ((code = readint(len)) != (1 << len) - 1) {
	cout << key[len][code];
      }
    }
    cout << endl;
    
    while (cin.peek() == '\n' && !cin.eof()) {
      cin.ignore(1);
    }
  }

  return 0;
}
