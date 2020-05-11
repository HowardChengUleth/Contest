#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
  string word;
  int id = 1;

  map<string, string> lang;

  lang["HELLO"] = "ENGLISH";
  lang["HOLA"] = "SPANISH";
  lang["HALLO"] = "GERMAN";
  lang["BONJOUR"] = "FRENCH";
  lang["CIAO"] = "ITALIAN";
  lang["ZDRAVSTVUJTE"] = "RUSSIAN";
  
  while (getline(cin, word) && word != "#") {
    cout << "Case " << id++ << ": ";
    if (lang.find(word) == lang.end()) {
      cout << "UNKNOWN" << endl;
    } else {
      cout << lang[word] << endl;
    }
  }

  return 0;
}
