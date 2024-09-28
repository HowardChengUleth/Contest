#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
  string T[] = { "@", "8", "(", "|)", "3", "#", "6", "[-]", "|", "_|",
		 "|<", "1", "[]\\/[]", "[]\\[]", "0", "|D", "(,)",
		 "|Z", "$", "']['", "|_|", "\\/", "\\/\\/", "}{", "`/", "2"};

  char c;
  while (cin.get(c)) {
    c = tolower(c);
    if (!isalpha(c)) {
      cout << c;
    } else {
      cout << T[c-'a'];
    }


  }

  

  return 0;
}
