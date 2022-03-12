#pragma once

#include "Formatter.h"
#include "BMPFileHeader.h"
#include "BMPInfoHeader.h"


class FormatterBMP : public Formatter {
private:
	//friend class BMPInfoHeader;
	//friend class BMPFileHeader;

public:

	void readLayer(string path, Layer &layer) override;

	void writeLayer(string path, const Layer &layer) override;


};