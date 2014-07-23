#include "AbstractGameObj.h"
#include <iostream>
AbstractGameObj::AbstractGameObj() : x(0.0), y(0.0), w(0), h(0), gravity(false), visible(false){}
AbstractGameObj::AbstractGameObj(double x2, double y2, int w2, int h2, bool grav, bool vis) : x(x2), y(y2), w(w2), h(h2), gravity(grav), visible(vis){}

AbstractGameObj::~AbstractGameObj(){
}