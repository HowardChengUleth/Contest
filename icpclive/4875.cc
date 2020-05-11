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

string code_nr(int len, int nr[])
{
  string result;
  int k = 0;
  while (len > 0) {
    int code_len = min(128, len);
    result += code(code_len-1);
    for (int i = 0; i < code_len; i++) {
      result += code(nr[k++]);
    }
    len -= code_len;
  }
  return result;
}

string code_nr(int len, int data)
{
  int nr[5000];
  for (int i = 0; i < len; i++) {
    nr[i] = data;
  }
  return code_nr(len, nr);
}

string code_r(int len, int data)
{
  string result;
  while (len >= 3) {
    int code_len = min(130, len);
    result += code(128 + code_len - 3) + code(data);
    len -= code_len;
  }
  result += code_nr(len, data);
  return result;
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

  string code;
  int nrlen = 0;
  int nr[5000];
  int i, j;
  for (i = 0; i < B; i = j) {
    for (j = i; j < B && data[j] == data[i]; j++)
      ;
    int len = j-i;
    if (len <= 2) {
      for (int k = 0; k < len; k++) {
	nr[nrlen++] = data[i+k];
      }
      continue;
    }

    code += code_nr(nrlen, nr);
    nrlen = 0;

    code += code_r(len, data[i]);
  }
  code += code_nr(nrlen, nr);

  cout << id << ' ' << code.length()/2 << endl;
  while (code.length() > 0) {
    cout << code.substr(0, 80) << endl;
    code.erase(0, 80);
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
