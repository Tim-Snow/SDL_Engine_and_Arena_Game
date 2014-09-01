#ifndef CHARSELECTSTATE_H_
#define CHARSELECTSTATE_H_

#include "../Engine/MenuSystem.h"
#include "PlayState.h"

enum playerStates { NOT_PLAYING, EDITING, READY };

struct playerQuarter{
	playerStates thisPlayerState;
	int selectedButton;
	SDL_Texture * background;
	SDL_Texture * status;
	SDL_GameController * cont;
	SDL_Rect statusPos;
	SDL_Rect pos;
	MenuButton accept;
	MenuButton back;
	MenuButton load;
	MenuButton save;
	MenuButton classSelect;
	MenuButton talents;
	MenuButton skill1;
	MenuButton skill2;
	MenuButton skill3;
	std::vector<MenuButton> buttons;

	playerQuarter(SDL_Rect p, SDL_GameController* c) : selectedButton(0), thisPlayerState(NOT_PLAYING){
		background = ResourceLoader::getResource("menuBG");
		if (c == nullptr){
			status = ResourceLoader::getResource("noConnectText");
		} else {
			status = ResourceLoader::getResource("pressButtonText");
		}

		pos = p; cont = c; 
		statusPos = { p.x + 20, p.y + 20, p.w - 40, 80 };
		SDL_Rect acceptButPos = { p.x + 20, p.y + pos.h - 100, p.w-40, 40 };
		accept.setTexture(ResourceLoader::getResource("acceptText")).setID(0).setPosition(acceptButPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
		acceptButPos.w = 60; acceptButPos.y += 60;
		load.setTexture(ResourceLoader::getResource("loadText")).setID(1).setPosition(acceptButPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
		acceptButPos.x += 75;
		save.setTexture(ResourceLoader::getResource("saveText")).setID(2).setPosition(acceptButPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });
		acceptButPos.x += 75;
		back.setTexture(ResourceLoader::getResource("backText")).setID(3).setPosition(acceptButPos).setFunc(nullptr).setBorderSize(10).setBorderCol({ 30, 30, 30, 255 }).setSelBorderCol({ 200, 200, 200, 255 });

		buttons.push_back(accept);
		buttons.push_back(back);
		buttons.push_back(load);
		buttons.push_back(save);
	}
};

class CharSelectState : public MenuSystem{
public:
	void init();
	void update(double d);
	void handleEvent();
	void draw();

	CharSelectState(){}
private:
	int readyPlayers;
	TextureItem title;
	SDL_Rect playMessageRect;
	std::vector<playerQuarter> players;
};
#endif /* defined (_CHARSELECTSTATE_H_)*/