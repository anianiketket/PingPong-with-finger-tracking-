#include "components.h"
#include "graphics.h"
#include<Windows.h>
#include <string.h>

int ID_ = 0;

player::player(void) {
	id = ID_++;
	color = RED;
	controlMode = keyboard;
	strcpy(name,"New Player");	
	score = 0;
	defaultPosition.length = 50;
	defaultPosition.width = 5;
	defaultPosition.x = 1;
	defaultPosition.y = 105;
	currentPosition = defaultPosition;
	lastPosition = currentPosition;
	ready = false;
}

void player::moveBat(double *cur_y) {
	lastPosition = currentPosition;
	if(controlMode == camera) {
		memcpy(yMemTemp,(void *)(mxGetPr(y_mxArray)),sizeof(double)*2);
		if(((yMemTemp[id] * 0.8) + currentPosition.length) <= 300 /*ARENA DIMENSION*/ && (yMemTemp[id] * 0.8) >= 0) {
			currentPosition.y = yMemTemp[id]*0.8;
		}
		else {
			currentPosition = lastPosition;
		}
	} else if(controlMode == keyboard) {
		if(id == 0) {
			if(GetAsyncKeyState(0x53)) {
				if(currentPosition.y+currentPosition.length <= 300) {
					currentPosition.y += 10;
				}
			}
			if(GetAsyncKeyState(0x57)) {
				if(currentPosition.y >= 1) {
					currentPosition.y -= 10;
				}
			}
		} else if (id == 1) {
			if(GetAsyncKeyState(VK_DOWN)) {
				if(currentPosition.y+currentPosition.length <= 300) {
					currentPosition.y += 10;
				}
			}
			if(GetAsyncKeyState(VK_UP)) {
				if(currentPosition.y >= 1) {
					currentPosition.y -= 10;
				}
			}	
		}
	}
}

void player::reset(void) {
	currentPosition = defaultPosition;
	lastPosition = currentPosition;
}

ball::ball(void) {
	ID = ring;
	defaultPosition.x = 255;
	defaultPosition.y = 155;
	defaultPosition.radius = 5;
	currentPosition = defaultPosition;
	lastPosition = currentPosition;
	ballDir.x = 1;
	ballDir.y = 1;
}

void ball::moveBall(void) {
	lastPosition = currentPosition;
	currentPosition.x = currentPosition.x + (SCALE*ballDir.x);
	currentPosition.y = currentPosition.y + (SCALE*ballDir.y);
}

bool ball::checkForBoundaryHit(void) {
	if((currentPosition.y-currentPosition.radius) < 0 || (currentPosition.y+currentPosition.radius) > 300) {
		return 1;
	} else {
		return 0;
	}
}

enum score ball::checkForScore(void) {
	if((currentPosition.x-currentPosition.radius) < 0) {	
		ballDir.x = 1;
		return scoreTwo;
	} else if ((currentPosition.x+currentPosition.radius) > 500){
		ballDir.x = -1;
		return scoreOne;
	} else {
		return none;
	}
}

bool ball::checkForHit(player one,player two) {
	if(currentPosition.x < 250 && currentPosition.x > 0) {
		if((currentPosition.y + currentPosition.radius) >= one.currentPosition.y && (currentPosition.y + currentPosition.radius) <= (one.currentPosition.y + one.currentPosition.length)) {
			return true;
		}
	}
	if(currentPosition.x > 250 && currentPosition.x < 500) {
		if((currentPosition.y + currentPosition.radius) >= two.currentPosition.y && (currentPosition.y + currentPosition.radius) <= (two.currentPosition.y + two.currentPosition.length)) {
			return true;
		}
	}
	return false;
}

void ball::reset(void) {
	currentPosition = defaultPosition;
	lastPosition = currentPosition;
}

arena::arena(void) {
	ID = classic;
	size.length = 500;
	size.width = 300;
	size.x = 0;
	size.y = 0;
	rectangle(size.x,size.y,size.length,size.width);
}

void arena::paintArena(player bat) {
	//Remove from last position
	setfillstyle(SOLID_FILL,BLACK);
	bar(bat.lastPosition.x,bat.lastPosition.y,(bat.lastPosition.width+bat.lastPosition.x),(bat.lastPosition.length+bat.lastPosition.y));
	//Show on new postion
	setfillstyle(SOLID_FILL,bat.color);
	bar(bat.currentPosition.x,bat.currentPosition.y,(bat.currentPosition.width+bat.currentPosition.x),(bat.currentPosition.length+bat.currentPosition.y));
}

void arena::paintArena(ball unit) {
	//Remove from last position
	setcolor(BLACK);
	circle((int)unit.lastPosition.x,(int)unit.lastPosition.y,(int)unit.lastPosition.radius);			
	//Show on new postion
	setcolor(WHITE);
	circle((int)unit.currentPosition.x,(int)unit.currentPosition.y,(int)unit.currentPosition.radius);
}

void arena::setArena(player bat) {
	setfillstyle(SOLID_FILL,bat.color);
	bar(bat.defaultPosition.x,bat.defaultPosition.y,(bat.defaultPosition.width+bat.defaultPosition.x),(bat.defaultPosition.length+bat.defaultPosition.y));
}

void arena::setArena(ball unit) {
	circle(unit.defaultPosition.x,unit.defaultPosition.y,unit.defaultPosition.radius);
}

void arena::setArena(void) {
	rectangle(size.x,size.y,size.length,size.width);
}