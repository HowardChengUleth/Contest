#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(void)
{
  int L, N;
  cin >> L >> N;
  
  map<string, string> irregular;
  for (int i = 0; i < L; i++) {
    string singular, plural;
    cin >> singular >> plural;
    irregular[singular] = plural;
  }

  const string vowels = "aeiou";

  for (int i = 0; i < N; i++) {
    string singular, plural;
    cin >> singular;

    int length = singular.length();
    if (irregular.find(singular) != irregular.end()) {
      plural = irregular[singular];
    } else if (length >= 2 && singular[length-1] == 'y' &&
	       vowels.find(singular[length-2]) == string::npos) {
      plural = singular.substr(0, length-1) + "ies";
    } else if (singular[length-1] == 'o' ||
	       singular[length-1] == 's' ||
	       singular[length-1] == 'x' ||
	       (singular[length-1] == 'h' && length >= 2 &&
		(singular[length-2] == 'c' || singular[length-2] == 's'))) {
      plural = singular + "es";
    } else {
      plural = singular + "s";
    }
    cout << plural << endl;
  }
  return 0;
}
