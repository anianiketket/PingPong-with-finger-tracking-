#ifndef components
#define components
#include "engine.h"

#define SCALE 10

enum playerCtrl {keyboard, camera};
enum arenaID {classic};
enum ballID {ring};
enum score {scoreOne,scoreTwo,none};

extern mxArray *y_mxArray;
extern double yMemTemp[2];

struct rect {
	float length;
	float width;
	double x;
	double y;
};

struct circle {
	float x;
	float y;
	float radius;
};

struct dir {
	char x;
	char y;
};

class player {
public :
	int id;
	int color;
	char name[20];
	enum playerCtrl controlMode;
	struct rect currentPosition, lastPosition,defaultPosition;
	int score;
	bool ready;
	void moveBat(double *cur_y);
	void reset(void);
	player(void);
private :
	
};

class ball {
public :
	enum ballID ID;
	struct circle currentPosition, lastPosition, defaultPosition;
	struct dir ballDir;
	void moveBall(void);
	bool checkForHit(player red,player blue);
	bool checkForBoundaryHit(void);
	enum score checkForScore(void);
	void reset(void);
	ball(void);
private :
};

class arena {
public :
	enum arenaID ID;
	struct rect size;
	arena(void);
	void paintArena(player bat);
	void paintArena(ball unit);
	void setArena(player bat);
	void setArena(ball unit);
	void setArena(void);
	void reset(void);
private :
};

#endif