#pragma once

#include "Formatter.h"

class FormatterPAM : public Formatter {
public:

	void readLayer(string path, Layer &layer) override;

	void writeLayer(string path, const Layer &layer) override;

};