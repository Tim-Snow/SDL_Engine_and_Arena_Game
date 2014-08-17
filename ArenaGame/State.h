#ifndef STATE_H_
#define STATE_H_

class Game;

class State{
public:
	virtual void init() = 0;
	virtual void clean() = 0;
	
	virtual void handleEvent(Game* g) = 0;
	virtual void draw(Game* g) = 0;
	virtual void update(Game* g) = 0;
protected:
private:
};

#endif /* defined (_STATE_H_)*/