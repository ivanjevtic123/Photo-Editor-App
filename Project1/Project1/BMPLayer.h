#pragma once

#include "Layer.h"
#include "BMPFileHeader.h"
#include "BMPInfoHeader.h"
#include "Pixel.h"
#include "Image.h"

class Layer;

//enum ImageType { BMP, PAM };

class BMPLayer : public Layer {
private:

	friend class FormatterBMP;
	friend class Selection;

	BMPFileHeader file_header;

	BMPInfoHeader bmp_info_header;

	std::vector<uint8_t> data; //Pixeli, 1 element ima 8 bita, npr FF
	//treba mi formula za kretanje kroz njega za po 4 elementa, uzeti u obzir height & width
	//mogu i klasu za Pixel
	///Pixel ***pixels;//iz data cu da uvezem u pixels



public:

	BMPLayer(string path) : Layer(path)/*, pixels(nullptr)*/ {}


	void importInMatrix() override {
		int z = 0;
		pixels = new Pixel**[bmp_info_header.height];
		for (int i = 0; i < bmp_info_header.height; i++) {
			pixels[i] = new Pixel*[bmp_info_header.width];
		}
		for (int i = bmp_info_header.height - 1; i >= 0; i--)
			for (int j = 0; j < bmp_info_header.width; j++) {
				int b = data[z]; z++;
				int g = data[z]; z++;
				int r = data[z]; z++;
				int a = data[z]; z++;
				pixels[i][j] = new Pixel(r, g, b, a);
			}
	}

	/*void importInMatrix() {
		int z = 0;
		pixels = new Pixel**[bmp_info_header.height];
		for (int i = 0; i < bmp_info_header.height; i++) {
			pixels[i] = new Pixel*[bmp_info_header.width];
			for (int j = 0; j < bmp_info_header.width; j++) {
				int a = data[z]; z++;
				int b = data[z]; z++;
				int g = data[z]; z++;
				int r = data[z]; z++;
				pixels[i][j] = new Pixel(r, g, b, a);
			}
		}
	}*/

	void exportToDataFromMatrix() override { //vratim u data, mogu na kraju kad cuvam da zovem tek
		int z = 0;
		for (int i = bmp_info_header.height - 1; i >= 0; i--) {
			for (int j = 0; j < bmp_info_header.width; j++) {
				int b = pixels[i][j]->getBlue(); data[z] = b; z++;
				int g = pixels[i][j]->getGreen(); data[z] = g; z++;
				int r = pixels[i][j]->getRed(); data[z] = r; z++;
				int a = pixels[i][j]->getAlpha(); data[z] = a; z++;
			}
		}
	}

	void destroyMatrix() { // u destructoru za BMPLayer cu ga zvati
		for (int i = 0; i < bmp_info_header.height; i++) {
			for (int j = 0; j < bmp_info_header.width; j++) {
				delete pixels[i][j];
			}
			delete[] pixels[i];
		}
		delete[] pixels;
		pixels = nullptr;
	}

	/*Pixel*** getMatrix() override {
		return pixels;
	}*/

	ImageType getImageType() const override { return BMP; }
	

};


