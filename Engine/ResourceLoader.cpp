#include "ResourceLoader.h"

string ResourceLoader::readTextFile(const char* path) {
	string content;
	ifstream fileStream(path, ios::in);

	if (!fileStream.is_open()) {
		cerr << "File could not be opened" << endl;
		return "";
	}

	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

SDL_Surface * ResourceLoader::loadBMP(const char* path){
	surf = SDL_LoadBMP(path);
	if (surf == nullptr){
		cout << "error reading in bmp" << endl;
	}
	return surf;
}
