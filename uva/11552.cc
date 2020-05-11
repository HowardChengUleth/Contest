// Sonny's test solution to CCPC 2008, Problem F
// September 16, 2008

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

const int sentry = 0x7fffffff;

struct section
{
    char first, last;
    int cost, total;

    section(char a = 0, char b = 0, int c = 0) 
        : first(a), last(b), cost(c), total(sentry) {}

    // try prepending with a previous string, and keep if better
    void prepend(const section &p) {
        int x = p.total + cost;         // add cost of this section
        if (p.last == first) --x;   // if characters match, we save a chunk
        total = min(total, x);
    }
};

// helper to turn a raw string piece into "sections"
void distill(string Si, vector<section> &v)
{
    set<char> s(Si.begin(), Si.end());

    // special case for strings with only 1 character type
    if (s.size() == 1) {
        char c = *s.begin();
        v.push_back(section(c, c, 1));
    }
    // otherwise, create a section prototype for each combination of first/last
    else {
        int cost = s.size();
        for (set<char>::iterator it = s.begin(); it != s.end(); ++it)
            for (set<char>::iterator jt = s.begin(); jt != s.end(); ++jt)
                if (*it != *jt)
                    v.push_back(section(*it, *jt, cost));
    }
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i)
    {
        int k;
        string S;

        cin >> k >> S;

        assert(S.size() % k == 0);

        int n = S.size() / k;

        // distill the input string into section prototypes
        vector< vector<section> > vv(n+1);
        for (int i = 1; i <= n; ++i) {
            string Si(S.begin() + k*(i-1), S.begin() + k*i);
            distill(Si, vv[i]);
        }

        // add a dummy starter in front
        section h; 
        h.total = 0;
        vv[0].push_back(h);

        // search for the string with fewest chunks
        for (int i = 0; i < n; ++i)
        {
            vector<section> &a = vv[i];
            vector<section> &b = vv[i+1];

            for (vector<section>::iterator jt = a.begin(); jt != a.end(); ++jt)
                for (vector<section>::iterator kt = b.begin(); kt != b.end(); ++kt)
                    kt->prepend(*jt);
        }

        int chunks = sentry;
        vector<section> &v = vv.back();
        for (vector<section>::iterator it = v.begin(); it != v.end(); ++it)
            chunks = min(chunks, it->total);

        cout << chunks << endl;

    }

    return 0;
}