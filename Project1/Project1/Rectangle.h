#pragma once

#include <stdio.h>

#include "Image.h"
#include "Selection.h"

using namespace std;


class Rectangle {
private:
	friend class Image;

	int posX, posY; //pozicija levog gornjeg ugla

	int height, width;

	bool status = true; //da li selektovani pixel selectujem ili unselectujem

public:

	Rectangle(int x, int y, int w, int h) {
		posX = x;
		posY = y;
		width = w;
		height = h;
	}

	void setActiveStatus() {
		status = true;
	}
	void setNotActiveStatus() {
		status = false;
	}

	bool getStatus() const {
		return status;
	}

	//getters:
	int getX() const {
		return posX;
	}
	int getY() const {
		return posY;
	}
	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}


	


};