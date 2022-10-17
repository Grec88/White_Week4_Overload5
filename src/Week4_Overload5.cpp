//============================================================================
// Name        : Week4_Overload5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <numeric>
#include <cmath>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
public:

	Rational() {
		p = 0;
		q = 1;
	}

	Rational(const int &numerator, const int &denominator) {
		if (numerator > 0 && denominator > 0) {
			p = numerator / gcd(numerator, denominator);
			q = denominator / gcd(numerator, denominator);
		}
		if (numerator == 0) {
			p = 0;
			q = 1;
		}
		if (numerator < 0 && denominator < 0) {
			p = abs(numerator) / gcd(abs(numerator), abs(denominator));
			q = abs(denominator) / gcd(abs(numerator), abs(denominator));
		}
		if ((denominator > 0 && numerator < 0)
				|| (denominator < 0 && numerator > 0)) {
			p = -(abs(numerator) / gcd(abs(numerator), abs(denominator)));
			q = abs(denominator) / gcd(abs(numerator), abs(denominator));
		}
	}

	int Numerator() const {
		return p;
	}

	int Denominator() const {
		return q;
	}

private:
	int p, q;
};


Rational operator+(const Rational &r1, const Rational &r2) {
	return Rational(
			(r1.Numerator() * r2.Denominator()
					+ r2.Numerator() * r1.Denominator()),
			(r1.Denominator() * r2.Denominator()));
}

Rational operator-(const Rational &r1, const Rational &r2) {
	return Rational(
			(r1.Numerator() * r2.Denominator()
					- r2.Numerator() * r1.Denominator()),
			(r1.Denominator() * r2.Denominator()));
}

Rational operator*(const Rational &r1, const Rational &r2) {
	return Rational(r1.Numerator() * r2.Numerator(),
			r1.Denominator() * r2.Denominator());
}

Rational operator/(const Rational &r1, const Rational &r2) {
	return Rational(r1.Numerator() * r2.Denominator(),
			r1.Denominator() * r2.Numerator());
}

bool operator==(const Rational &r1, const Rational &r2) {
	if ((r1.Numerator() == r2.Numerator())
			&& (r1.Denominator() == r2.Denominator())) {
		return true;
	} else {
		return false;
	}
}

bool operator<(const Rational& r1, const Rational& r2){
	if((r1 - r2).Numerator() < 0){
		return true;
	}
	return false;
}

bool operator>(const Rational& r1, const Rational& r2){
	if(!(r1 < r2)){
		return true;
	}
	return false;
}

ostream& operator<<(ostream &stream, const Rational &r) {
	stream << r.Numerator() << '/' << r.Denominator();
	return stream;
}

istream& operator>>(istream &stream, Rational &r) {
	int p, q ;
	char c ;
	if(!stream){
		return stream;
	}
	stream >> p;
	if(!stream){
		return stream;
	}
	stream >> c;
	if( c != '/'){
		return stream;
	}
	stream >> q;
	if(!stream){
		return stream;
	}
	r = Rational(p, q);
	return stream;
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

