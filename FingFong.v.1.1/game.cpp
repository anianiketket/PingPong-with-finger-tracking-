#include <stdio.h>
#include "graphics.h"
#include <Windows.h>
#include "engine.h"
#include "components.h"
#define clrscr() system("cls")

char GAMESPEED = 50; //in milliseconds. This is the default speed if both the players are playing with keyboard
mxArray *y_mxArray = mxCreateDoubleMatrix(1,2,mxREAL);
double yMemTemp[2];

void main()
{
	int gd,gm,gresult;
	char buff[50];
	
	Engine *ep;
	
	//Intialise Grpahics for C
	detectgraph(&gd,&gm);
	initgraph(&gd,&gm,"C:\\ TC\\BGI");
	gresult = graphresult();
	if(gresult != grOk)
	{
		printf(grapherrormsg(gresult));
		getch();
	}

	/*Default game components loaded*/
	player one,two;
	two.defaultPosition.x = 495;
	two.currentPosition = two.defaultPosition;
	two.lastPosition = two.currentPosition;
	two.color = BLUE;
	ball unityBall;
	arena classic_ar;

	one.controlMode = camera;
	two.controlMode = keyboard;

mainmenu:
	clrscr();
	cleardevice();
	/*
	//Load main menu
	while(1) {
		if(GetAsyncKeyState(VK_UP)) {
			//Move Cursor Up		
		} else if(GetAsyncKeyState(VK_DOWN)) {
			//Move cursor down
		} else if(GetAsyncKeyState(VK_RETURN)) {
			//Select option
		}
		//Configure the player, ball and arena and modes. When done "break"
	}
	*/
	//Configure Main Menu customizations
	if(one.controlMode == camera || two.controlMode == camera) {
		/*Initialize MATLAB engine*/
		GAMESPEED = 1;				//Game Speed reduced due to high processing time taken by camera control mode.
		
		printf("Loading MATLAB engine.\n");
		ep = engOpen("Null");
		printf("MATLAB engine loaded.\n");

		/*Initialise webcam using MATLAB. Here cd should contain the path where the MATLAB function is located*/
		printf("Loading webcam...\n");
		engEvalString(ep,"cd('C:/FingFong.v.1.1.MATLAB'); global vidh vidw cam threshold brightness contrast lowerArea upperArea; brightness = [0,0]; contrast = [1,1]; threshold = [0,0,0,0,0,0;0,0,0,0,0,0]; vidh = 640; vidw = 480; cam = webcam('Integrated Webcam');");
		printf("Webcam Loaded...\n");
		
		if(one.controlMode == camera) {
			printf("Loading token configuration for %s...\n",one.name);
			engEvalString(ep,"UI(1); config=0;");
			printf("Configuration done.\n",one.name);
		}
		if(two.controlMode == camera) { 
			printf("Loading token configuration for %s...\n",two.name);
			engEvalString(ep,"UI(2);");
			printf("Configuration done.\n");
		}
		
		printf("Initializing global variables..\n");
		engEvalString(ep,"global state_playerOne state_playerTwo P_playerOne P_playerTwo Ex; KalmanFilterInit(); P_playerOne = Ex; P_playerTwo = Ex; state_playerOne = [0;0;0;0]; state_playerTwo = [0;0;0;0];");
		engEvalString(ep,"close all");
		printf("All initializaions done.\n");

	}
	
	//Run infinite loops for game
	while(1)
	{
		//Initial conditions for game
		printf("Setting up arena..\n");
		classic_ar.setArena();
		classic_ar.setArena(unityBall);
		classic_ar.setArena(one);
		classic_ar.setArena(two);
		one.reset();
		two.reset();
		unityBall.reset();
		
		sprintf(buff,"%s %d      %s %d",one.name,one.score,two.name,two.score);
		outtextxy(1,310,buff);

		printf("Arena set.\n Press any key to start the game.\n");

		getch();
		//Move ball
		while(1)
		{
			classic_ar.setArena();
			if(GetAsyncKeyState(VK_ESCAPE)) {
				printf("ESCAPE was pressed.\n");
				char userInput = getch();
				while(userInput != 'y' && userInput != 'n') {
					userInput = getch();
				}
				if(userInput == 'y') {
					//goto mainmenu;
					goto escape;
				} else {
					//Continue game
				}
			}
			if(GetAsyncKeyState(0x52)) {
				printf("R was pressed.\n");
				char userInput = getch();
				while(userInput != 'y' && userInput != 'n') {
					userInput = getch();
				}
				if(userInput == 'y') {
					one.score = 0;
					two.score = 0;
					goto newround;
				} else {
					//Continue game
				}
			}
			if(one.controlMode == camera || two.controlMode == camera) {	
				//Take input from MATLAB object tracking function
				engEvalString(ep,"y = Run(1);");
				//Transferring values from MATLAB workspace to C
				y_mxArray = engGetVariable(ep,"y");
			}			
			//Move bat
			one.moveBat(&one.currentPosition.y);
			two.moveBat(&two.currentPosition.y);
			//Move ball
			if(unityBall.checkForBoundaryHit())
			{
				unityBall.ballDir.y = -unityBall.ballDir.y;
			} else if(((unityBall.currentPosition.x-unityBall.currentPosition.radius) <= (one.currentPosition.width+1)) || ((unityBall.currentPosition.x+unityBall.currentPosition.radius) >= (classic_ar.size.length - (two.currentPosition.width + 1)))) { //elseif Check for Bat hit
				if(unityBall.checkForHit(one,two)) {
					unityBall.ballDir.x = -unityBall.ballDir.x;
				} else {
					switch (unityBall.checkForScore()) {
					case scoreOne :
						one.score++;
						goto newround;					//Set scores.
					case scoreTwo :
						two.score++;
						goto newround;
					case none :
						break;
					}
				}
			}
			unityBall.moveBall();
			classic_ar.paintArena(unityBall);
			classic_ar.paintArena(one);
			classic_ar.paintArena(two);
			delay(GAMESPEED);
		}
newround:
		printf("Starting new round.\n");
		cleardevice();
	}
escape:
	printf("Quitting the game..\n");
	if(one.controlMode == camera || two.controlMode == camera) {	
		engEvalString(ep,"clear all");
		engEvalString(ep,"close all");
		engClose(ep);
	}
	printf("Press any key to close the console.\n");
	getch();
	closegraph();
}
