#include <iostream>
#include <string>

using namespace std;

string instruction[16] = {
  "ADD", "SUB", "MUL", "DIV", "MOV", "BREQ", "BRLE", "BRLS", "BRGE",
  "BRGR", "BRNE", "BR", "AND", "OR", "XOR", "NOT" 
};

int num_ops[16] = {
  2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1
};

int value(char ch)
{
  if (isdigit(ch)) {
    return ch - '0';
  } else {
    return ch - 'A' + 10;
  }
}

void read_operand(void)
{
  int code = 0;
  int val = 0;
  char ch;
  string prefix[4] = { "R", "$", "PC+", "" };

  cin >> ch;
  code = value(ch) >> 2;
  val = value(ch) & 0x3;
  for (int i = 1; i < 4; i++) {
    cin >> ch;
    val <<= 4;
    val |= value(ch);
  }
  cout << prefix[code] << val;
}

int main(void)
{
  char ch;

  while (cin >> ch) {
    int code = value(ch);
    cout << instruction[code] << ' ';
    for (int i = 0; i < num_ops[code]; i++) {
      if (i) cout << ',';
      read_operand();
    }
    cout << endl;
  }
  return 0;
}
