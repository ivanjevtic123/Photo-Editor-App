#pragma once

#include <string>
#include <stdio.h>
#include <iostream>

#include "Pixel.h"
#include "Image.h"


using namespace std;

enum ImageType { BMP, PAM };


class Layer {
protected:

	friend class Selection;
	friend class Image;

	string imagePath;

	bool active = false; //dodati u ktr

	bool visible = false; //dodati u ktr

	Pixel ***pixels = nullptr;//dodao zbog polimorfizma

	int width = 0;
	int height = 0;

public:

	Layer(string path) : imagePath(path) {}

	virtual void importInMatrix() = 0;

	virtual void exportToDataFromMatrix() = 0;

	//virtual Pixel*** getMatrix() = 0;//GetMatrix koji zelim da menjam???

	void setWidth(int w) {
		width = w;
	}
	void setHeight(int h) {
		height = h;
	}

	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}


	virtual ImageType getImageType() const = 0;
		//enum ImageType { BMP, PAM };
};

//prozirnost 0..100