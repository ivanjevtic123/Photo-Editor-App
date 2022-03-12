#include <fstream>
#include <iostream>
#include <regex>
#include <stdint.h>

#include "formatter.h"
#include "FormatterPAM.h"
#include "PAMLayer.h"


//mogu i pomocne nizove da cuvam, i hocu

void FormatterPAM::readLayer(string path, Layer &layer) {

	PAMLayer &pam = (PAMLayer &)layer;

	std::ifstream inputFile(path.c_str(), std::ios_base::binary);

	if (inputFile) {
		uint16_t file_type;
		inputFile.read((char*)&file_type, 2); //P7
		if (file_type != 0x3750) {
			cout << "Los PAM fajl!" << endl;
			return;
		}
		uint8_t help_array[46];
		char arr[10];

		inputFile.read((char*)help_array, 7);

		int i = 0;
		inputFile.read(&arr[i], 1);
		while (isdigit(arr[i])) {
			i++;
			inputFile.read(&arr[i], 1);
		}
		i++;
		arr[i] = '\0';
		pam.width = atoi(arr);

		inputFile.read((char*)help_array, 7);

		i = 0;
		inputFile.read(&arr[i], 1);
		while (isdigit(arr[i])) {
			i++;
			inputFile.read(&arr[i], 1);
		}
		i++;
		arr[i] = '\0';
		pam.height = atoi(arr);

		inputFile.read((char*)help_array, 45);

		uint64_t num_of_bytes = pam.width * pam.height * 4;
		uint8_t *temp = new uint8_t[num_of_bytes];
		inputFile.read((char *)temp, num_of_bytes);
		for (int i = 0; i < num_of_bytes; i++)
			pam.data.push_back(temp[i]);
		delete temp;
		inputFile.close();

		//image.createMatrix(); //populate matrix of pixels from data array
	}
	else {
		cout << "Greska prilikom otvaranja fajla!" << endl;
	}



}


void FormatterPAM::writeLayer(string path, const Layer &layer) {

	PAMLayer &pam = (PAMLayer &)layer;

	//pam.dumpMatrix(); //dump pixels to data array

	std::ofstream outFile(path.c_str(), std::ios_base::binary);

	if (outFile) {
		uint8_t first[9] = { 0x50, 0x37, 0x0A, 0x57, 0x49, 0x44, 0x54, 0x48, 0x20 };
		outFile.write((char *)first, 9);

		char dim[10];
		sprintf(dim, "%d", pam.width);
		for (int i = 0; i < strlen(dim); i++)
			outFile.write((char *)(dim + i), 1);

		uint8_t second[8] = { 0x0A, 0x48, 0x45, 0x49, 0x47, 0x48, 0x54, 0x20 };
		outFile.write((char *)second, 8);

		sprintf(dim, "%d", pam.height);
		for (int i = 0; i < strlen(dim); i++)
			outFile.write((char *)(dim + i), 1);

		uint8_t third[46] = {
			0x0A, 0x44, 0x45, 0x50, 0x54, 0x48, 0x20, 0x34, 0x0A, 0x4D,
			0x41, 0x58, 0x56, 0x41, 0x4C, 0x20, 0x32, 0x35, 0x35, 0x0A,
			0x54, 0x55, 0x50, 0x4C, 0x54, 0x59, 0x50, 0x45, 0x20, 0x52,
			0x47, 0x42, 0x5F, 0x41, 0x4C, 0x50, 0x48, 0x41, 0x0A, 0x45,
			0x4E, 0x44, 0x48, 0x44, 0x52, 0x0A };
		outFile.write((char *)third, 46);

		uint64_t num_of_bytes = pam.width * pam.height * 4;
		uint8_t *temp = pam.data.data();
		outFile.write((char *)temp, num_of_bytes);
		outFile.close();
	}
	else {
		cout << "Greska prilikom otvaranja fajla!" << endl;
	}

}