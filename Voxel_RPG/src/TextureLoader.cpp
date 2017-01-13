
/*
void Texture::Load2DTexture(Texture& texture) {

	unsigned char* image = ImageLoader::loadImageData(texture.getImagePaths()[0], &texture.m_U, &texture.m_V, &texture.m_comp);

	if (image == nullptr) {
		std::cout << "TEXTURE LOAD FAILED::ImageData[" + texture.getImagePaths()[0] + "]" << std::endl;
		return;
	}
	else {
		std::cout << "TEXTURE LOAD SUCCESSFUL::ImageData[" + texture.getImagePaths()[0] + "]" << std::endl;
	}

	// ~~~~~ SET UP TEXTURE ON GPU ~~~~
	GLuint textureID = OpenGLMemoryTracker::AllocateTexture();


	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.m_U, texture.m_V, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Free image from CPU memory
	ImageLoader::freeImageData(image);

	// ~~~~~ SETTING TEXTURE OBJECT VALUES ~~~~~
	texture.m_textureID = textureID;

}

GLuint Texture::Load2DTextureArray(std::vector<std::string> imagePaths, int maxu, int maxv) {

	GLuint texture = OpenGLMemoryTracker::AllocateTexture();
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, maxu, maxv, imagePaths.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	for (unsigned int i = 0; i < imagePaths.size(); i++) {
		int u, v, comp;
		unsigned char* image = ImageLoader::loadImageData(imagePaths[i], &u, &v, &comp);
		std::cout << u << std::endl;
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, u, v, 1, GL_RGBA, GL_UNSIGNED_BYTE, image);
		ImageLoader::freeImageData(image);
	}

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	return texture;

}

void Texture::LoadCubeMapTexture(Texture& texture) {

	GLuint textureID = OpenGLMemoryTracker::AllocateTexture();

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (GLuint i = 0; i < texture.getImagePaths().size(); i++) {
		unsigned char* image = ImageLoader::loadImageData(texture.getImagePaths()[0], &texture.m_U, &texture.m_V, &texture.m_comp);

		if (image == nullptr) {
			std::cout << "TEXTURE LOAD FAILED::ImageData[" + texture.getImagePaths()[0] + "]" << std::endl;
			return;
		}
		else {
			std::cout << "TEXTURE LOAD SUCCESSFUL::ImageData[" + texture.getImagePaths()[0] + "]" << std::endl;
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, texture.getU(), texture.getV(), 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			ImageLoader::freeImageData(image);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// ~~~~~ SETTING TEXTURE OBJECT VALUES ~~~~~
	texture.m_textureID = textureID;

}
*/