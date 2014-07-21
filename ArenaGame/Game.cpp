#include "Game.h"

Game::Game(){
	GameObject a;
	GameObject * b = new GameObject(50, 50);
	GameObject * c = new GameObject(100, 100, 100);
	gameObjects.push_back(a);
	gameObjects.push_back(*b);
	gameObjects.push_back(*c);
}

Game::~Game(){

}