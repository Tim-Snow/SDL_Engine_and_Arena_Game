#ifndef STATE_H_
#define STATE_H_

enum MENU_COMMANDS { UP, DOWN, LEFT, RIGHT, ACCEPT, BACK, EXIT, NONE };

#include "ResourceLoader.h"
#include "GraphicsEngine.h"
#include "InputManager.h"

class State{
public:
	void start(std::shared_ptr<GraphicsEngine> g, std::shared_ptr<InputManager> i){ gfx = g; input = i; }

	virtual void init() = 0;
	virtual void clean() = 0;
	virtual void handleEvent() = 0;
	virtual void draw() = 0;
	virtual void update(double d) = 0;
protected:
	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<InputManager> input;
};

class StateManager{
public:
	static StateManager& instance(){
		static StateManager *instance = new StateManager();
		return *instance;
	}

	void setup(std::shared_ptr<GraphicsEngine> g, std::shared_ptr<InputManager> i){ gfx = g; input = i; }

	State * getState()			{ return states.back(); }
	void	pushState(State* s)	{ states.push_back(s); states.back()->start(gfx, input); input->pollEvent(); states.back()->handleEvent(); states.back()->init(); }
	void	popState()			{ states.back()->clean(); states.pop_back(); input->pollEvent();  states.back()->handleEvent(); }

	void clean(){
		while (!states.empty()){
			states.back()->clean();
			states.pop_back();
		}
	}
private:
	StateManager(){}
	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<InputManager> input;
	std::vector<State*> states;
};

#endif /* defined (_STATE_H_)*/