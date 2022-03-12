#pragma once

#include "Operation.h"

//Da li da zadrzim number u parent klasi, mzd bude ovako pravilo probleme???

class Saberi : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

	int num;

public:

	Saberi(int number, bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		num = number;
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) override {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(curr.getRed() + num);
				curr.setGreen(curr.getGreen() + num);
				curr.setBlue(curr.getBlue() + num);
			}
		}
		else {
			curr.setRed(curr.getRed() + num);
			curr.setGreen(curr.getGreen() + num);
			curr.setBlue(curr.getBlue() + num);	
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return ADD; }

	int getNum() const {
		return num;
	}

};



class Oduzmi : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

	int num;

public:

	Oduzmi(int number, bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		num = number;
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(curr.getRed() - num);
				curr.setGreen(curr.getGreen() - num);
				curr.setBlue(curr.getBlue() - num);
			}
		}
		else {
			curr.setRed(curr.getRed() - num);
			curr.setGreen(curr.getGreen() - num);
			curr.setBlue(curr.getBlue() - num);	
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return SUB; }

	int getNum() const {
		return num;
	}
};



class InverznoOduzmi : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

	int num;
	
public:

	InverznoOduzmi(int number, bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		num = number;
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(num - curr.getRed());
				curr.setGreen(num - curr.getGreen());
				curr.setBlue(num - curr.getBlue());
			}
		}
		else {
			curr.setRed(num - curr.getRed());
			curr.setGreen(num - curr.getGreen());
			curr.setBlue(num - curr.getBlue());
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return INVSUB; }

	int getNum() const {
		return num;
	}
};



class Pomnozi : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

	int num;

public:

	Pomnozi(int number, bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		num = number;
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(curr.getRed() * num);
				curr.setGreen(curr.getGreen() * num);
				curr.setBlue(curr.getBlue() * num);
			}
		}
		else {
			curr.setRed(curr.getRed() * num);
			curr.setGreen(curr.getGreen() * num);
			curr.setBlue(curr.getBlue() * num);	
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return MUL; }

	int getNum() const {
		return num;
	}
};



class Podeli : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

	int num;

public:

	Podeli(int number, bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		num = number;
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(curr.getRed() / num);
				curr.setGreen(curr.getGreen() / num);
				curr.setBlue(curr.getBlue() / num);
			}
		}
		else {
			curr.setRed(curr.getRed() / num);
			curr.setGreen(curr.getGreen() / num);
			curr.setBlue(curr.getBlue() / num);
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return DIV; }

	int getNum() const {
		return num;
	}
};



class InverznoPodeli : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

	int num;

public:

	InverznoPodeli(int number, bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		num = number;
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(num / curr.getRed());
				curr.setGreen(num / curr.getGreen());
				curr.setBlue(num / curr.getBlue());
			}
		}
		else {
			curr.setRed(num / curr.getRed());
			curr.setGreen(num / curr.getGreen());
			curr.setBlue(num / curr.getBlue());
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return INVDIV; }

	int getNum() const {
		return num;
	}
};



class Power : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

	int num;

public:

	Power(int number, bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		num = number;
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(pow(curr.getRed(), num));
				curr.setGreen(pow(curr.getGreen(), num));
				curr.setBlue(pow(curr.getBlue(), num));
			}
		}
		else {
			curr.setRed(pow(curr.getRed(), num));
			curr.setGreen(pow(curr.getGreen(), num));
			curr.setBlue(pow(curr.getBlue(), num));
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return POW; }

	int getNum() const {
		return num;
	}
};



class Log : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

public:

	Log(bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(std::log(curr.getRed()));
				curr.setGreen(std::log(curr.getGreen()));
				curr.setBlue(std::log(curr.getBlue()));
			}
		}
		else {
			curr.setRed(std::log(curr.getRed()));
			curr.setGreen(std::log(curr.getGreen()));
			curr.setBlue(std::log(curr.getBlue()));
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return LOG; }

	int getNum() const override {
		return -1;
	}
};



class Abs : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

public:

	Abs(bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(std::abs(curr.getRed()));
				curr.setGreen(std::abs(curr.getGreen()));
				curr.setBlue(std::abs(curr.getBlue()));
			}
		}
		else {
			curr.setRed(std::abs(curr.getRed()));
			curr.setGreen(std::abs(curr.getGreen()));
			curr.setBlue(std::abs(curr.getBlue()));
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return ABS; }

	int getNum() const override {
		return -1;
	}
};



class Min : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

	int num;

public:

	Min(int number, bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		num = number;
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				if (curr.getRed() > num) curr.setRed(num);
				if (curr.getGreen() > num) curr.setGreen(num);
				if (curr.getBlue() > num) curr.setBlue(num);
			}
		}
		else {
			if (curr.getRed() > num) curr.setRed(num);
			if (curr.getGreen() > num) curr.setGreen(num);
			if (curr.getBlue() > num) curr.setBlue(num);
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return MIN; }

	int getNum() const {
		return num;
	}
};



class Max : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

	int num;

public:

	Max(int number, bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		num = number;
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				if (curr.getRed() < num) curr.setRed(num);
				if (curr.getGreen() < num) curr.setGreen(num);
				if (curr.getBlue() < num) curr.setBlue(num);
			}
		}
		else {
			if (curr.getRed() < num) curr.setRed(num);
			if (curr.getGreen() < num) curr.setGreen(num);
			if (curr.getBlue() < num) curr.setBlue(num);
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return MAXIM; }

	int getNum() const {
		return num;
	}
};


//...................................................................................
//PREDEFINISANE FJE:


class Inverzija : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

public:

	Inverzija(bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(255 - curr.getRed());
				curr.setGreen(255 - curr.getGreen());
				curr.setBlue(255 - curr.getBlue());
			}
		}
		else {
			curr.setRed(255 - curr.getRed());
			curr.setGreen(255 - curr.getGreen());
			curr.setBlue(255 - curr.getBlue());
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return INV; }

	int getNum() const override {
		return -1;
	}
};



class PretvoriUSivo : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

public:

	PretvoriUSivo(bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed((curr.getRed() + curr.getGreen() + curr.getBlue()) / 3);
				curr.setGreen((curr.getRed() + curr.getGreen() + curr.getBlue()) / 3);
				curr.setBlue((curr.getRed() + curr.getGreen() + curr.getBlue()) / 3);
			}
		}
		else {
			curr.setRed((curr.getRed() + curr.getGreen() + curr.getBlue()) / 3);
			curr.setGreen((curr.getRed() + curr.getGreen() + curr.getBlue()) / 3);
			curr.setBlue((curr.getRed() + curr.getGreen() + curr.getBlue()) / 3);
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return GRAY; }

	int getNum() const override {
		return -1;
	}
};



class PretvoriUCrnoBelo : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

public:

	PretvoriUCrnoBelo(bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				if (((curr.getRed() + curr.getGreen() + curr.getBlue()) / 3) < 127) {
					curr.setRed(0);
					curr.setGreen(0);
					curr.setBlue(0);
				}
				else {
					curr.setRed(255);
					curr.setGreen(255);
					curr.setBlue(255);
				}
			}
		}
		else {
			if (((curr.getRed() + curr.getGreen() + curr.getBlue()) / 3) < 127) {
				curr.setRed(0);
				curr.setGreen(0);
				curr.setBlue(0);
			}
			else {
				curr.setRed(255);
				curr.setGreen(255);
				curr.setBlue(255);
			}
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return BNW; }

	int getNum() const override {
		return -1;
	}
};



//dovrsi!!!
class Medijana : public Operation {
private:

	bool arrOfOperations = false;

	bool lastOperation = false;

	Pixel ***matrix;

public:

	Medijana(Pixel ***pixels, bool flag = false, bool opArr = false, bool last = false) : Operation(flag) {
		matrix = pixels; //samo po vrednosti mi treba
		arrOfOperations = opArr;
		lastOperation = last;
	}

	//getters:
	bool getArrFlag() const {
		return arrOfOperations;
	}
	bool getLastFlag() const {
		return lastOperation;
	}

	//setters:
	void setArrFlag(bool flag) {
		arrOfOperations = flag;
	}
	void setLastFlag(bool flag) {
		lastOperation = flag;
	}

	void execution(Pixel &curr) override {
		if (selectionExists) {
			if (curr.checkActive()) {
				curr.setRed(255 - curr.getRed());
				curr.setGreen(255 - curr.getGreen());
				curr.setBlue(255 - curr.getBlue());
			}
		}
		else {
			curr.setRed(255 - curr.getRed());
			curr.setGreen(255 - curr.getGreen());
			curr.setBlue(255 - curr.getBlue());
		}
		//CheckAndFixPixel:
		if (getArrFlag() == true) {
			if (getLastFlag() == true) curr.checkAndFixRGB();
		}
		else {
			curr.checkAndFixRGB();
		}
	}

	OperationType getOperationType() override { return MED; }

	int getNum() const override {
		return -1;
	}
};
