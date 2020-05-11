#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string AtoI[5] = {
  ".***.. ****.. .****. ****.. *****. *****. .****. *...*. *****.",
  "*...*. *...*. *...*. *...*. *..... *..... *..... *...*. ..*...",
  "*****. ****.. *..... *...*. ***... ***... *..**. *****. ..*...",
  "*...*. *...*. *..... *...*. *..... *..... *...*. *...*. ..*...",
  "*...*. ****.. .****. ****.. *****. *..... .***.. *...*. *****."
};

string JtoR[5] = {
  "..***. *...*. *..... *...*. *...*. .***.. ****.. .***.. ****..",
  "...*.. *..*.. *..... **.**. **..*. *...*. *...*. *...*. *...*.",
  "...*.. ***... *..... *.*.*. *.*.*. *...*. ****.. *...*. ****..",
  "*..*.. *..*.. *..... *...*. *..**. *...*. *..... *..**. *..*..",
  ".**... *...*. *****. *...*. *...*. .***.. *..... .****. *...*."
};

string Sto_[5] = {
  ".****. *****. *...*. *...*. *...*. *...*. *...*. *****. ......",
  "*..... *.*.*. *...*. *...*. *...*. .*.*.. .*.*.. ...*.. ......",
  ".***.. ..*... *...*. .*.*.. *.*.*. ..*... ..*... ..*... ......",
  "....*. ..*... *...*. .*.*.. **.**. .*.*.. ..*... .*.... ......",
  "****.. .***.. .***.. ..*... *...*. *...*. ..*... *****. ......"
};


string paper[60];

void write_text(char c, int R, int C)
{
  if (0 <= R && R < 60 && 0 <= C && C < 60 && c != '.' && c != ' ') {
    paper[R][C] = c;
  }
}

void write_charC5(char c, int R, int C)
{
  string *s;
  int offset;
  
  if ('A' <= c && c <= 'I') {
    s = AtoI;
    offset = (c - 'A')*7;
  } else if ('J' <= c && c <= 'R') {
    s = JtoR;
    offset = (c - 'J')*7;
  } else {
    s = Sto_;
    offset = ((c == ' ') ? 8 : (c - 'S'))*7;
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      write_text(s[i][offset+j], R+i, C+j);
    }
  }
}

void write_text(string S, int R, int C, string font)
{
  if (font == "C1") {
    for (int i = 0; i < S.length(); i++) {
      write_text(S[i], R, C+i);
    }
  } else {
    for (int i = 0; i < S.length(); i++) {
      write_charC5(S[i], R, C+i*6);
    }
  }
}


bool solve()
{
  for (int i = 0; i < 60; i++) {
    paper[i] = string(60, '.');
  }

  string cmd;
  if (!(cin >> cmd)) return false;
  while (cmd != ".EOP") {
    string font;
    int R, C;
    string S;
    cin >> font >> R;
    R--;
    if (cmd == ".P") {
      cin >> C;
      C--;
    }
    

    char c;
    while (cin.get(c) && c != '|')
      ;
    getline(cin, S);
    while (S[S.length()-1] != '|') {
      S.erase(S.length()-1);
    }
    S.erase(S.length()-1);

    int charwidth = (font == "C1") ? 1 : 6;
    int linewidth = S.length() * charwidth;
    
    if (cmd == ".L") {
      C = 0;
    } else if (cmd == ".R") {
      C = 60 - linewidth;
    } else if (cmd == ".C") {
      if (linewidth % 2 == 0) {
	C = (60 - linewidth)/2;
      } else {
	if (60 >= linewidth) {
	  C = (60 - linewidth + 1)/2;
	} else {
	  C = -(linewidth - 60)/2;
	}
      }
    }

    write_text(S, R, C, font);
    cin >> cmd;
  }

  for (int i = 0; i < 60; i++) {
    cout << paper[i] << endl;
  }
  cout << endl << string(60, '-') << endl << endl;

  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
