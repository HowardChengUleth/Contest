#include <bits/stdc++.h>

using namespace std;

map<char,string> tohex;

void init()
{
  tohex['0'] = "0000";
  tohex['1'] = "0001";
  tohex['2'] = "0010";
  tohex['3'] = "0011";
  tohex['4'] = "0100";
  tohex['5'] = "0101";
  tohex['6'] = "0110";
  tohex['7'] = "0111";
  tohex['8'] = "1000";
  tohex['9'] = "1001";
  tohex['A'] = "1010";
  tohex['B'] = "1011";
  tohex['C'] = "1100";
  tohex['D'] = "1101";
  tohex['E'] = "1110";
  tohex['F'] = "1111";
}

typedef long long ll;

ll intval(const string &s, int start, int len)
{
  ll v = 0;
  for (int i = 0; i < len; i++) {
    v = v*2 + s[start+i] - '0';
  }
  return v;
}

ll parse(const string &bin, int &num_read, int s = 0);

ll decode_literal(const string &bin, int &num_read, int s)
{
  ll val = 0;
  
  bool done = false;
  num_read = 0;
  while (!done) {
    // read next 5 bits
    num_read += 5;
    done = bin[s] == '0';
    val = val * 16 + intval(bin, s+1, 4);
    s += 5;
  }

  return val;
}

ll decode_operator(const string &bin, int &num_read, int s)
{
  int length_type = bin[s] - '0';
  s += 1;
  num_read = 1;

  ll ver = 0;
  if (length_type == 0) {
    ll len = intval(bin, s, 15);
    num_read += 15;
    s += 15;

    while (len > 0) {
      int count;
      ver += parse(bin, count, s);
      s += count;
      len -= count;
      num_read += count;
    }
  } else if (length_type == 1) {
    ll num = intval(bin, s, 11);
    num_read += 11;
    s += 11;
    for (int i = 0; i < num; i++) {
      int count;
      ver += parse(bin, count, s);
      s += count;
      num_read += count;
    }

  } else {
    assert(false);
  }
  
  return ver;
}

ll parse(const string &bin, int &num_read, int s)
{
  ll ver = intval(bin, s, 3);
  s += 3;
  ll type = intval(bin, s, 3);
  s += 3;
  num_read = 6;

  int count;
  if (type == 4) {
    decode_literal(bin, count, s);
    num_read += count;
    s += count;
  } else {
    // operator
    ver += decode_operator(bin, count, s);
    num_read += count;
    s += count;
  }
  return ver;
}


int main()
{
  init();
  
  string s;
  while (cin >> s) {
    string bin;
    for (auto c : s) {
      bin += tohex[c];
    }

    int dummy;
    cout << parse(bin, dummy) << endl;
  }

  return 0;
}
