#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<string> Paragraph;
typedef vector<Paragraph> Article;

void read_paragraph(Paragraph &p, bool &more_p, bool &more_a)
{
  p.clear();
  
  vector<string> lines;
  string line;
  while (getline(cin, line) && line.length() > 0 && line != "***" &&
	 line != "******") {
    lines.push_back(line);
  }
  more_p = line != "***" && line != "******";
  more_a = more_p || line != "******";

  // break into sentences
  unsigned int line_no = 0, j = 0;
  while (line_no < lines.size()) {
    // look for the start of sentence
    while (line_no < lines.size() && j < lines[line_no].length() &&
	   lines[line_no][j] == ' ') {
      if (++j == lines[line_no].length()) {
	line_no++;
	j = 0;
      }
    }

    if (line_no >= lines.size()) return;

    string sentence;

    sentence += lines[line_no][j];

    // look for . ? !
    while (line_no < lines.size() && j < lines[line_no].length() &&
	   lines[line_no][j] != '.' && lines[line_no][j] != '?' &&
	   lines[line_no][j] != '!') {
      if (++j == lines[line_no].length()) {
	line_no++;
	j = 0;					
	if (line_no < lines.size()) {
	  sentence += '\n';
	}
      }
      if (line_no < lines.size()) {
	sentence += lines[line_no][j];
      }
    }

    if (sentence.length() > 0) {
      char last = sentence[sentence.length()-1];
      if (last == '.' || last == '?' || last == '!') {
    	p.push_back(sentence);
      }
    }
    if (line_no < lines.size() && ++j == lines[line_no].length()) {
      line_no++;
      j = 0;
    }
  }
}

bool read_article(Article &a)
{
  a.clear();

  while (1) {
    Paragraph p;
    bool more_p, more_a;

    read_paragraph(p, more_p, more_a);
    if (p.size() >= 3) {
      a.push_back(p);
    }
    if (!more_p) {
      return !more_a;
    }
  }
}

#include <sstream>
#include <set>

set<string> get_words(string s)
{
  for (unsigned int i = 0; i < s.length(); i++) {
    if (!isalpha(s[i])) {
      s[i] = ' ';
    } else {
      s[i] = tolower(s[i]);
    }
  }
  
  istringstream iss(s);
  string word;
  set<string> words;
  while (iss >> word) {
    words.insert(word);
  }
  return words;
}

string select_topic(const Paragraph &p)
{
  int best;
  int best_score = -1;

  vector< set<string> > words;
  for (unsigned int i = 0; i < p.size(); i++) {
    words.push_back(get_words(p[i]));
  }

  for (unsigned int i = 0; i < p.size(); i++) {
    int score = 0;
    set<string> after;
    for (unsigned int j = i+1; j < p.size(); j++) {
      after.insert(words[j].begin(), words[j].end());
    }
    for (set<string>::const_iterator it = words[i].begin();
	 it != words[i].end(); ++it) {
      if (after.find(*it) != after.end()) {
	score++;
      }
    }

    if (best_score == -1 || score > best_score) {
      best_score = score;
      best = i;
    }
  }
  return p[best];
}

void process(const Article &a)
{
  for (unsigned int i = 0; i < a.size(); i++) {
    string topic = select_topic(a[i]);
    cout << topic << endl;
  }
  if (a.size() == 0) {
    cout << endl;
  }
}

int main(void)
{
  Article article;
  bool done;
  do {
    done = read_article(article);
    process(article);
    cout << "======" << endl;
  } while (!done);
  article.clear();
  return 0;
}
