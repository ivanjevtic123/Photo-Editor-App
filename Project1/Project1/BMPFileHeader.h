#pragma once
#pragma pack(push, 1)

#include <stdint.h>

class BMPFileHeader {
protected:
	uint16_t file_type{ 0x4D42 };          // File type always BM which is 0x4D42
	uint32_t file_size{ 0 };               // Size of the file (in bytes)
	uint16_t reserved1{ 0 };               // Reserved, always 0
	uint16_t reserved2{ 0 };               // Reserved, always 0
	uint32_t offset_data{ 0 };             // Start position of pixel data (bytes from the beginning of the file)

	friend class FormatterBMP;
	friend class Selection;

};

#pragma pack(pop)