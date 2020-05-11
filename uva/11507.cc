#include <iostream>
#include <string>

using namespace std;

void change(string &dir, const string &bend)
{
  if (bend == "+y") {
    if (dir == "+x") {
      dir = "+y";
    } else if (dir == "-x") {
      dir = "-y";
    } else if (dir == "+y") {
      dir = "-x";
    } else if (dir == "-y") {
      dir = "+x";
    }
  } else if (bend == "-y") {
    if (dir == "+x") {
      dir = "-y";
    } else if (dir == "-x") {
      dir = "+y";
    } else if (dir == "+y") {
      dir = "+x";
    } else if (dir == "-y") {
      dir = "-x";
    }    
  } else if (bend == "+z") {
    if (dir == "+x") {
      dir = "+z";
    } else if (dir == "-x") {
      dir = "-z";
    } else if (dir == "+z") {
      dir = "-x";
    } else if (dir == "-z") {
      dir = "+x";
    }
  } else if (bend == "-z") {
    if (dir == "+x") {
      dir = "-z";
    } else if (dir == "-x") {
      dir = "+z";
    } else if (dir == "+z") {
      dir = "+x";
    } else if (dir == "-z") {
      dir = "-x";
    }
  }
}

int main(void)
{
  int L;
  while (cin >> L && L) {
    string dir = "+x";
    string bend;
    for (int i = 0; i < L-1; i++) {
      cin >> bend;
      change(dir, bend);
    }
    cout << dir << endl;
  }
  return 0;
}
