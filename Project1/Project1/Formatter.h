#pragma once

#include <string>

#include "image.h"
#include "Layer.h"

using namespace std;


class Formatter {
public:

	virtual void readLayer(string path, Layer &image) = 0;

	virtual void writeLayer(string path, const Layer &image) = 0;


};


