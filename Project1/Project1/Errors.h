#pragma once

#include <iostream>
#include <string>
#include <exception>


using namespace std;

class ErrorInPixelValue : public exception {
	string poruka = "Greska u vrednosti dela pixela!!!";
	void pisi(ostream &out) const {
		out << poruka << endl;
	}
public:

	friend ostream& operator<<(ostream& out, const ErrorInPixelValue& e) {
		e.pisi(out);
		return out;
	}
};


