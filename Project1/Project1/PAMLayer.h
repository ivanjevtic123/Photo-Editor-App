#pragma once

#include "Layer.h"
#include "Pixel.h"
#include "Image.h"

class Layer;

class PAMLayer : public Layer {
private:

	friend class FormatterPAM;

	//int width, height; //u parenta sam stavio

	std::vector<uint8_t> data;


public:

	PAMLayer(string path) : Layer(path) {}

	void importInMatrix() override {
		int z = 0;
		pixels = new Pixel**[height];
		for (int i = 0; i < height; i++) {
			pixels[i] = new Pixel*[width];
		}
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int r = data[z]; z++;
				int g = data[z]; z++;
				int b = data[z]; z++;
				int a = data[z]; z++;
				pixels[i][j] = new Pixel(r, g, b, a);
			}
		}
	}
	
	void exportToDataFromMatrix() override { 
		int z = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int r = pixels[i][j]->getRed(); data[z] = r; z++;
				int g = pixels[i][j]->getGreen(); data[z] = g; z++;
				int b = pixels[i][j]->getBlue(); data[z] = b; z++;
				int a = pixels[i][j]->getAlpha(); data[z] = a; z++;
			}
		}
	}

	void destroyMatrix() { // u destructoru za BMPLayer cu ga zvati
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				delete pixels[i][j];
			}
			delete[] pixels[i];
		}
		delete[] pixels;
		pixels = nullptr;
	}

	ImageType getImageType() const override { return PAM; }
};