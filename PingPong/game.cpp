#include<stdio.h>
#include "graphics.h"
#include<Windows.h>
#include "engine.h"
#define clrscr() system("cls")

struct
{
	int ballx;
	int bally;
	int radius;
}ball={255,155,5};
struct
{
	int length;
	int width;
	int batx;
	int baty;
}red={50,5,1,105},blue={50,5,495,105};

//Initialize all game components.
void init(void)
{
	//Draw all components with a frame
	circle(ball.ballx,ball.bally,ball.radius);
	setfillstyle(SOLID_FILL,RED);
	bar(red.batx,red.baty,red.width+red.batx,red.length+red.baty);
	setfillstyle(SOLID_FILL,BLUE);
	bar(blue.batx,blue.baty,blue.width+blue.batx,blue.length+blue.baty);
	rectangle(0,0,500,300);
}

//Ball moving function according to direction.
void moveball(int *current_x,int *current_y,int *dir_x,int *dir_y)
{
	*current_x=*current_x+5*(*dir_x);
	*current_y=*current_y+5*(*dir_y);
}

char CheckForBoundaryHit(int y)
{
	char flag=0;
	if(y+ball.radius<0 || y+ball.radius>300)
		flag=1;
	return flag;
}

char CheckForScore(int x)
{
	char flag=0;
	if(x-ball.radius<0 || x+ball.radius>500) flag=1;
	return flag;
}

char CheckForHit(int y,int c_bat_y)
{
	char flag=0;
	if(y+ball.radius>=c_bat_y && y+ball.radius<=c_bat_y+50)
		flag=1;
	return flag;
}
/*
void movebats(double *c_red_y,double *l_red_y,double *c_blue_y,double *l_blue_y)
{
	if(GetAsyncKeyState(0x53))
	{
		if(*c_red_y+50<=300)
		{
		*l_red_y=*c_red_y;
		*c_red_y=*c_red_y+10;
		}
	}

	if(GetAsyncKeyState(0x57))
	{
		if(*c_red_y>=1)
		{
		*l_red_y=*c_red_y;
		*c_red_y=*c_red_y-10;
		}
	}

	if(GetAsyncKeyState(VK_DOWN))
	{
		if(*c_blue_y+50<=300)
		{
		*l_blue_y=*c_blue_y;
		*c_blue_y=*c_blue_y+10;
		}
	}

	if(GetAsyncKeyState(VK_UP))
	{	if(*c_blue_y>=1)
		{
		*l_blue_y=*c_blue_y;
		*c_blue_y=*c_blue_y-10;
		}
	}	
}
*/
void main()
{
	int gd,gm,gresult,scorered=0,scoreblue=0,c_ball_x,c_ball_y,dir_x,dir_y,l_ball_x,l_ball_y;
	double c_red_y,c_blue_y,l_red_y,l_blue_y;
	char buff[50];
	
	//Initialize MATLAB engine
	Engine *ep;
	ep = engOpen("Null");
	mxArray *y_red = mxCreateDoubleMatrix(1,1,mxREAL),*y_blue = mxCreateDoubleMatrix(1,1,mxREAL);	
	
	clrscr();
	
	//Intialise Grpahics for C
	detectgraph(&gd,&gm);
	initgraph(&gd,&gm,"C:\\ TC\\BGI");
	gresult = graphresult();
	if(gresult != grOk)
	{
		printf(grapherrormsg(gresult));
		getch();
	}

	dir_x=1;
	dir_y=1;
	
	//Initialise webcam using MATLAB. Here cd should contain the path where the MATLAB function is located
	engEvalString(ep,"cam = webcam;  cd('D:/MATLAB projects/GestureTetris/');");

	//Run infinite loops for game
	while(1)
	{
		//Initial conditions for game
		init();
		c_red_y=red.baty;
		l_red_y=c_red_y;
		c_blue_y=blue.baty;
		l_blue_y=c_blue_y;
		c_ball_x=ball.ballx;
		c_ball_y=ball.bally;
		l_ball_x=c_ball_x;
		l_ball_y=c_ball_y;
		sprintf(buff,"RED %d      BLUE %d",scorered,scoreblue);
		outtextxy(1,310,buff);
		
		//Move ball
		while(1)
		{
			rectangle(0,0,500,300);
			if(GetAsyncKeyState(VK_ESCAPE)) 
				goto escape;
			
			//Take input from MATLAB object tracking function
			engEvalString(ep,"[yred,yblue]=CallObjectTrack(640,480,cam);");
			
			//Transferring values from MATLAB workspace to C
			y_red=engGetVariable(ep,"yred");
			y_blue=engGetVariable(ep,"yblue");
			l_red_y=c_red_y;
			l_blue_y=c_blue_y;
			memcpy(&c_red_y,(void *)(mxGetPr(y_red)),sizeof(double));
			memcpy(&c_blue_y,(void *)(mxGetPr(y_blue)),sizeof(double));
			
			//Move bats accordingly
			//movebats(&c_red_y,&l_red_y,&c_blue_y,&l_blue_y);
			if(((c_red_y*0.62)+50)<=300 && (c_red_y*0.62)>=0) 
				c_red_y=(int)(c_red_y*0.62);
			else
				c_red_y=l_red_y;
			if(((c_blue_y*0.62)+50)<=300 && (c_blue_y*0.62)>=0) 		
				c_blue_y=(int)(c_blue_y*0.62);
			else
				c_blue_y=l_blue_y;


			if(CheckForBoundaryHit(c_ball_y))
			{
				dir_y=(-dir_y);
				moveball(&c_ball_x,&c_ball_y,&dir_x,&dir_y);
			}
			else if((c_ball_x-ball.radius<=1)||(c_ball_x+ball.radius>=495))//elseif Check for Bat hit
			{
				   if((c_ball_x<250 && CheckForHit(c_ball_y,c_red_y)) || (c_ball_x>250 && CheckForHit(c_ball_y,c_blue_y)))
				   {
					dir_x=(-dir_x);
					moveball(&c_ball_x,&c_ball_y,&dir_x,&dir_y);
				   }
				   else
				   {
					if(c_ball_x>250)
					{
						scorered++;
						dir_x=-1;
					}
					else
					{
						scoreblue++;
						dir_x=1;
					}
					break;
					//Set scores.
				   }
			}
			else
			{
				moveball(&c_ball_x,&c_ball_y,&dir_x,&dir_y);
			}

			//Remove from last position
			setcolor(BLACK);
			circle(l_ball_x,l_ball_y,ball.radius);
			setfillstyle(SOLID_FILL,BLACK);
			bar(red.batx,l_red_y,red.width+red.batx,red.length+l_red_y);
			bar(blue.batx,l_blue_y,blue.width+blue.batx,blue.length+l_blue_y);
			
			//Show on new postion
			setcolor(WHITE);
			circle(c_ball_x,c_ball_y,ball.radius);
			setfillstyle(SOLID_FILL,RED);
			bar(red.batx,c_red_y,red.width+red.batx,red.length+c_red_y);
			setfillstyle(SOLID_FILL,BLUE);
			bar(blue.batx,c_blue_y,blue.width+blue.batx,blue.length+c_blue_y);
			l_ball_x=c_ball_x;
			l_ball_y=c_ball_y;
			}
		cleardevice();
	}
escape:
engEvalString(ep,"clear");
getch();
engClose(ep);
closegraph();
}