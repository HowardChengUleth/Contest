#include <bits/stdc++.h>

using namespace std;

struct Fraction
{
    int64_t num, denom;

    Fraction(int64_t nn, int64_t dd)
	: num{nn}, denom{dd}
    {
	int64_t g = gcd(num, denom);
	num /= g;
	denom /= g;
	assert(num >= 0 && denom > 0);
    }

    bool operator==(const Fraction &f1) const
    {
	return num == f1.num && denom == f1.denom;
    }

    bool operator!=(const Fraction &f1) const
    {
	return !((*this) == f1);
    }

    bool operator<(const Fraction &f1) const
    {
	return num * f1.denom < f1.num * denom;
    }
};

ostream &operator<<(ostream &os, const Fraction &f)
{
    os << f.num;
    if (f.denom != 1) {
	os << " / " << f.denom;
    }

    return os;
}


int main()
{
    int M, N;
    cin >> M >> N;

    vector<int64_t> T(M), X(N);

    for (auto &t : T) {
	cin >> t;
    }

    for (auto &x : X) {
	cin >> x;
    }

    set<Fraction> poss_speed;
    set<int64_t> dist;
    for (int i = 0; i+M-1 < N; i++) {
	Fraction speed{X[i+1]-X[i], T[1]-T[0]};
	//	cout << "i, i+1 = " << i << ' ' << i+1 << " : " << speed << endl;
	bool same = true;
	for (int j = 0; j < M-1 && same; j++) {
	    Fraction speed2{X[i+j+1] - X[i+j], T[j+1]-T[j]};
	    //	    cout << "i+j+1, i+j = " << i+j+1 << ' ' << i+j
	    //		 << " : " << speed2 << endl;
	    if (speed != speed2) {
		same = false;
	    }
	}
	if (same) {
	    poss_speed.insert(speed);
	    dist.insert(X[i+1]-X[i]);
	}
    }

    cout << poss_speed.size() << endl;
    for (auto d : dist) {
	cout << d << ' ';
    }
    cout << endl;
    

    
    return 0;
}
