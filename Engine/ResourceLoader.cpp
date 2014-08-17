#include "ResourceLoader.h"

ResourceLoader::ResourceLoader(){
	IMG_Init(IMG_INIT_PNG);
}

ResourceLoader::~ResourceLoader(){
	IMG_Quit();
}

std::string ResourceLoader::readTextFile(const char* t) {
	std::string content;
	std::ifstream fileStream(t, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "File could not be opened" << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}
SDL_Surface * ResourceLoader::loadImage(const char* i){
	SDL_Surface * surf = nullptr;
	surf = IMG_Load(i);
	if (surf == nullptr){
		std::cout << "Cannot access path for: " << i << std::endl;
	}
	return surf;
}


SDL_Surface * ResourceLoader::loadBMP(const char* i){
	SDL_Surface * surf = nullptr;
	surf = SDL_LoadBMP(i);
	if (surf == nullptr){
		std::cout << "Cannot access path for: " << i << std::endl;
	}
	return surf;
}
