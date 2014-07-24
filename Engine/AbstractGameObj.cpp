#include "AbstractGameObj.h"
#include <iostream>
AbstractGameObj::AbstractGameObj() : gravity(false), visible(false){}
AbstractGameObj::AbstractGameObj(double x, double y, int w, int h, bool grav, bool vis) : gravity(grav), visible(vis){}

AbstractGameObj::~AbstractGameObj(){}