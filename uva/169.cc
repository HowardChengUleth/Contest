#include <string>
#include <iostream>
#include <cctype>

using namespace std;

const int MAX_STRING = 1000;
const int MAX_SPACER = MAX_STRING + 1;
const int MAX_WORDS = MAX_STRING + 2 * 26;

struct Position {
  unsigned int start, finish;
  bool first, repeated, overlaps, both;

  void init(unsigned int start, unsigned int finish) {
    this->start = start;
    this->finish = finish;
    first = true;
    repeated = overlaps = both = false;
  }
};

Position word[MAX_WORDS];
string message;
int word_count;


void add_word(unsigned int start, unsigned int finish)
{
  int temp = finish - start + 1;
  if (2 <= temp && temp <= 250) {
    /* check length of potential word */
    word[word_count].init(start, finish);
    word_count++;
  }
}

void scan(void)
{
  int start[26];      /* where is the last time we saw the character for
			 a match to the left */

  /* the first letter is a "joker" and can match anything */
  for (int i = 0; i < 26; i++) {
    start[i] = -1;
  }

  /* mark all the words that are not bracketed by the last joker */
  for (unsigned int finish = 0; finish < message.length(); finish++) {
    add_word(start[message[finish]-'a'] + 1, finish-1);
    start[message[finish]-'a'] = finish;
  }

  /* add the remaining words bracketed by the last joker (but not the whole
     message */
  for (int i = 0; i < 26; i++) {
    if (start[i] >= 0) {
      add_word(start[i]+1, message.length()-1);
    }
  }

}

void mark_repeated(void)
{
  int count[MAX_WORDS][26];

  /* get frequency count of each word */
  for (int i = 0; i < word_count; i++) {
    for (int j = 0; j < 26; j++) {
      count[i][j] = 0;
    }
    for (unsigned int j = word[i].start; j <= word[i].finish; j++) {
      count[i][message[j]-'a']++;
    }
  }

  /* mark all of the pairs of words which are the same up to permutation */
  for (int i = 0; i < word_count; i++) {
    if (word[i].repeated) continue;
    for (int j = i+1; j < word_count; j++) {
      if (word[i].finish - word[i].start ==
	  word[j].finish - word[j].start) {
	bool same = true;
	for (int ch = 0; ch < 26 && same; ch++) {
	  same = (count[i][ch] == count[j][ch]);
	}
	if (same) {
	  word[i].repeated = word[j].repeated = true;
	  word[j].first = false;
	}
      }
    }
  }
}

void mark_overlap(void)
{

  for (int i = 0; i < word_count; i++) {
    if (!word[i].repeated) continue;
    for (int j = i+1; j < word_count; j++) {
      if (!word[j].repeated) continue;
      if (word[j].start <= word[i].finish) {
	word[i].overlaps = word[j].overlaps = true;
      }
    }
  }
}

void mark_both(void)
{
  int count[MAX_WORDS][26];
  
  for (int i = 0; i < word_count; i++) {
    if (word[i].repeated) {
      for (int j = 0; j < 26; j++) {
	count[i][j] = 0;
      }
      for (unsigned int j = word[i].start; j <= word[i].finish; j++) {
	count[i][message[j]-'a']++;
      }
    }
  }

  for (int i = 0; i < word_count; i++) {
    if (word[i].first && word[i].repeated) {
      if (word[i].overlaps) {
	word[i].both = true;
      } else {

	/* word[i] may not overlap but maybe the same as another word that
	   overlaps */
	for (int j = i+1; j < word_count; j++) {
	  if (word[j].repeated && 
	      word[i].finish - word[i].start == word[j].finish - word[j].start) {
	    bool same = true;
	    for (int ch = 0; ch < 26 && same; ch++) {
	      same = (count[i][ch] == count[j][ch]);
	    }
	    if (same && word[j].overlaps) {
	      word[i].both = true;
	    }
	  }
	}
      }
    }
  }
}

void print_solution(void)
{
  for (int i = 0; i < word_count; i++) {
    if (word[i].first && word[i].both) {
      for (unsigned int j = word[i].start; j <= word[i].finish; j++) {
	cout << message[j];
      }
      cout << endl;
    }
  }
}

int main(void)
{
  string line;

  while (getline(cin, line) && line != "#") {
    bool end_line;

    if (line.length() > 0) {
      end_line = (line[line.length()-1] != '-');
    } else {
      end_line = true;
    }
    // get rid of nonletters
    for (int i = line.length()-1; i >= 0; i--) {
      if (!islower(line[i])) {
	line.erase(i, 1);
      }
    }
    message += line;

    if (end_line) {
      scan();
      mark_repeated();
      mark_overlap();
      mark_both();
      print_solution();

      message = "";
      word_count = 0;
      cout << "*" << endl;
    }
  }

}
