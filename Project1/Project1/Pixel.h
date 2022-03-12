#pragma once

#include "Errors.h"


class Pixel{
private:

	bool active = false;

	int red, green, blue, alpha;

	friend class BMPLayer;
	friend class PAMLayer;
public:

	Pixel(int r = 0, int g = 0, int b = 0, int a = 0, bool flag = false) {
		if (r < 0 || r > 255) throw ErrorInPixelValue();
		else red = r;

		if (g < 0 || g > 255) throw ErrorInPixelValue();
		else green = g;

		if (b < 0 || b > 255) throw ErrorInPixelValue();
		else blue = b;

		if (a < 0 || a > 255) throw ErrorInPixelValue();//ne 100 nego 255[px], ne %
		else alpha = a;

		active = flag;
	}

	/*void setActive() {
		active = true;
	}
	void setNotActive() {
		active = false;
	}*/

	void setActive(bool flag) {
		active = flag;
	}

	bool checkActive() const {
		return active;
	}

	//rgbaGetters:
	int getRed() const {
		return red;
	}
	int getGreen() const {
		return green;
	}
	int getBlue() const {
		return blue;
	}
	int getAlpha() const {
		return alpha;
	}

	//rgbaSetters:
	void setRed(int r) {
		red = r;
	}
	void setGreen(int g) {
		green = g;
	}
	void setBlue(int b) {
		blue = b;
	}
	void setAlpha(int a) {
		alpha = a;
	}

	//check&Fixers:
	void checkAndFixRGB() {//check&Fix
		if (red > 255) red = 255;
		if (red < 0) red = 0;

		if (green > 255) green = 255;
		if (green < 0) green = 0;

		if (blue > 255) blue = 255;
		if (blue < 0) blue = 0;
	}




};