#include <iostream>
#include <cctype>

using namespace std;

int main(void)
{
  string line;

  while (getline(cin, line)) {
    int count = 0;
    bool inword = false;

    for (unsigned int i = 0; i < line.length(); i++) {
      if (isalpha(line[i])) {
	inword = true;
      } else if (inword) {
	inword = false;
	count++;
      }
    }
    if (inword) {
      count++;
    }
    cout << count << endl;
  }
  return 0;
}
