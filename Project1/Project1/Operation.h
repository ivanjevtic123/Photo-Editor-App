#pragma once

#include <stdio.h>
#include <math.h>

#include "Image.h"

enum OperationType { ADD, SUB, INVSUB, MUL, DIV, INVDIV, POW, LOG, ABS, MIN, MAXIM, INV, GRAY, BNW, MED, COMP };

using namespace std;

class Operation { //pa i ovde mi treba virtua

protected:

	bool selectionExists = false;

	//int num;//argument za operacije//mozda u children da ga ubacim

public:

	Operation(/*int number, */int flag = false) {
		//num = number;
		selectionExists = flag;
	}

	void setSelectionExists(bool flag = false) { //setuj ga pri prvoj selekciji, unsetuj pri brijsanju selekcije(ako bude brisanja)
		selectionExists = flag; 
	}

	bool getSelectionExists() const {
		return selectionExists;
	}

	virtual void execution(Pixel &curr) = 0;

	virtual void setLastFlag(bool flag) = 0;

	virtual OperationType getOperationType() = 0;

	virtual int getNum() const = 0;
};