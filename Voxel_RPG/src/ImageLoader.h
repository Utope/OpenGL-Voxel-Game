#pragma once
#include <string>

class ImageLoader {
public:
	static unsigned char* loadImageData(std::string& filePath, int* u, int* v, int* comp);
	static unsigned char* loadImageData(std::string& filePath, int* u, int* v);
	static unsigned char* loadImageData(std::string& filePath);
	static void freeImageData(unsigned char*);
};