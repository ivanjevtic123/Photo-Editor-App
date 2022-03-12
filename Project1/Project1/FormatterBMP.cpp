#include <fstream>
#include <iostream>

#include "formatter.h"
#include "FormatterBMP.h"
#include "BMPLayer.h"
#include "BMPFileHeader.h"
#include "BMPInfoHeader.h"

using namespace std;

void FormatterBMP::readLayer(string path, Layer &layer) {//image
	//citanje bmp
	BMPLayer &bmp = (BMPLayer &)layer; //trebalo bi koriscenjem dynamic_cast i pokazivaca, ovako je nebezbedno

	std::ifstream inp(path.c_str(), std::ios_base::binary);

	if (inp) {
		inp.read((char*)&bmp.file_header.file_type, 2);
		inp.read((char*)&bmp.file_header.file_size, 4);
		inp.read((char*)&bmp.file_header.reserved1, 2);
		inp.read((char*)&bmp.file_header.reserved2, 2);
		inp.read((char*)&bmp.file_header.offset_data, 4);

		if (bmp.file_header.file_type != 0x4D42) {
			cout << "Greska los BMP fajl!" << endl;
		}
		inp.read((char*)&bmp.bmp_info_header.size, 4);
		inp.read((char*)&bmp.bmp_info_header.width, 4);
		inp.read((char*)&bmp.bmp_info_header.height, 4);
		inp.read((char*)&bmp.bmp_info_header.planes, 2);
		inp.read((char*)&bmp.bmp_info_header.bit_count, 2);
		inp.read((char*)&bmp.bmp_info_header.compression, 4);
		inp.read((char*)&bmp.bmp_info_header.size_image, 4);
		inp.read((char*)&bmp.bmp_info_header.x_pixels_per_meter, 4);
		inp.read((char*)&bmp.bmp_info_header.y_pixels_per_meter, 4);
		inp.read((char*)&bmp.bmp_info_header.colors_used, 4);
		inp.read((char*)&bmp.bmp_info_header.colors_important, 4);

		// Jump to the pixel data location
		inp.seekg(bmp.file_header.offset_data, inp.beg);

		uint64_t num_of_bytes = bmp.bmp_info_header.width * bmp.bmp_info_header.height * bmp.bmp_info_header.bit_count / 8;
		uint8_t *temp = new uint8_t[num_of_bytes];
		inp.read((char *)temp, num_of_bytes);
		//inp.read(reinterpret_cast<char*>(temp), num_of_bytes);
		for (int i = 0; i < num_of_bytes; i++) {
			bmp.data.push_back(temp[i]);  //pixeli
		}

		delete temp;
		inp.close();//dodao

		//za selekciju:
		bmp.setHeight(bmp.bmp_info_header.height);//DODAJ ZA PAM!!!
		bmp.setWidth(bmp.bmp_info_header.width);
	}
	else {
		cout << "Greska prilikom otvaranja ulaznog fajla!" << endl;
	}

}

void FormatterBMP::writeLayer(string path, const Layer &layer) {
	BMPLayer &bmp = (BMPLayer &)layer;

	std::ofstream outp(path.c_str(), std::ios_base::binary);

	if (outp) {
		if (bmp.bmp_info_header.bit_count == 32) {

			outp.write((const char*)&bmp.file_header, sizeof(bmp.file_header));
			outp.write((const char*)&bmp.bmp_info_header, sizeof(bmp.bmp_info_header));

			outp.write((const char*)bmp.data.data(), bmp.data.size());
		}
		else {
			throw std::runtime_error("Greska: Program radi samo sa 32b BMP fajlovima!");
		}

	}
	else {
		throw std::runtime_error("Greska prilikom otvaranja izlaznog fajla!");
	}

	outp.close(); //dodao sam


}