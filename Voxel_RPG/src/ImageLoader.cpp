#include "ImageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned char* ImageLoader::loadImageData(std::string& imagePath, int* u, int* v, int* comp) {
	return stbi_load(imagePath.c_str(), u, v, comp, STBI_rgb_alpha);
}
unsigned char* ImageLoader::loadImageData(std::string& imagePath, int* u, int* v) {
	int* comp = nullptr;
	return stbi_load(imagePath.c_str(), u, v, comp, STBI_rgb_alpha);
}
unsigned char* ImageLoader::loadImageData(std::string& imagePath) {
	int* comp = nullptr;
	int* u = nullptr;
	int* v = nullptr;
	return stbi_load(imagePath.c_str(), u, v, comp, STBI_rgb_alpha);
}
void ImageLoader::freeImageData(unsigned char* image) {
	stbi_image_free(image);
}