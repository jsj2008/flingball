//
// C++ Implementation: globals
//
// Description: 
//
//
// Author: Nick Payne
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <sstream>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_framerate.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "Include/Box2D.h"

using namespace std;

#include "globals.h"
#include "ball.h"
#include "level.h"
#include "camera.h"
//#include "player.h"
//#include "sound.h"
//----------------------------------------------------------
//----------------------------------------------------------

SDL_Surface *screen;
CCamera camera;

int mainEditor(int argc, char* args[]) {
		// for fps counter
	int startTime;
	int frameTime;
	int fps;
	
	int quit = 0;
	
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(-100.0f, -100.0f);
	worldAABB.upperBound.Set(100.0f, 100.0f);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Do we want to let bodies sleep?
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(worldAABB, gravity, doSleep);
	
	// SDL init
	cout << "Starting up...(" << argc << ")" << endl;
	cout << "Initialising SDL..." << endl;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	cout << "SDL Video init OK..." << endl;
	atexit(SDL_Quit);
	// screen init
	screen = SDL_SetVideoMode(EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF);
	
	if (screen == NULL) {
		//fprintf(stderr, "Couldn't set 640x480x32 video mode: %s\n", SDL_GetError());
		cout << "Couldn't set " << EDITOR_SCREEN_WIDTH << "x" << EDITOR_SCREEN_HEIGHT << "x" << EDITOR_SCREEN_HEIGHT << "x" << EDITOR_SCREEN_BPP << ": " << SDL_GetError() << endl;
		return 1;
	}
	SDL_WM_SetCaption("Fling Ball Editor", NULL);
	cout << "Set Video mode " << EDITOR_SCREEN_WIDTH << "x" << EDITOR_SCREEN_HEIGHT << "x" << EDITOR_SCREEN_HEIGHT << " OK" << endl;
	
	CLevel *level;
	level = new CLevel;
	
	camera.setViewport(EDITOR_VIEWPORT_X, EDITOR_VIEWPORT_Y, EDITOR_VIEWPORT_W, EDITOR_VIEWPORT_H);
	/**************
	** game loop **
	**************/
	SDL_Event event;
	
	
	int mouseX = 0;
	int mouseY = 0;
	while(!quit) {
		// FPS
		startTime = SDL_GetTicks();
		
		/**************************************
		** event handling & processing stuff **
		**************************************/
		//player->stop();
		
			
		while (SDL_PollEvent(&event)) {  // we need a while loop as there may be several events in the queue
			switch (event.type) {
				case SDL_QUIT:
					quit = 1;
					break;
					
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {						
						
					}
					break;
					
				case SDL_MOUSEBUTTONUP:
					
					break;
								
				case SDL_MOUSEMOTION:
					mouseX = event.motion.x;
					mouseY = event.motion.y;
					break;
			}
		}
		
		if (keyPressed(SDLK_ESCAPE)) {
			quit = 1;
			break;
		}
		
		/********************
		** rendering stuff **
		********************/
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));  // white layer
		
		SDL_Flip(screen);  // flip back buffer -> screen
		
		//SDL_framerateDelay(fpsman);
		
		frameTime = SDL_GetTicks()-startTime;
		fps = (frameTime>0) ? 1000 / frameTime : 0;
		SDL_Delay(25);
	}
	
	delete level;

	cout << "Exiting..." << endl;
	SDL_Quit();
	cout << "Done." << endl;
	return 0;
}

int mainGame(int argc, char* args[]) {
	// for fps counter
	int startTime;
	int frameTime;
	int fps;
	
	int quit = 0;
	
	// SDL init
	cout << "Starting up...(" << argc << ")" << endl;
	cout << "Initialising SDL..." << endl;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	cout << "SDL Video init OK..." << endl;
	atexit(SDL_Quit);
	// screen init
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF);
	
	if (screen == NULL) {
		//fprintf(stderr, "Couldn't set 640x480x32 video mode: %s\n", SDL_GetError());
		cout << "Couldn't set " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << "x" << SCREEN_HEIGHT << "x" << SCREEN_BPP << ": " << SDL_GetError() << endl;
		return 1;
	}
	//SDL_ShowCursor(SDL_DISABLE);  // get rid of cursor
	SDL_WM_SetCaption("Fling Ball", NULL);
	cout << "Set Video mode " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << "x" << SCREEN_HEIGHT << " OK" << endl;

	//SDL_EnableKeyRepeat(1, 1);

	/********************
	** game init stuff **
	********************/
	//CWorld *world;  // define the world
	//CEvent eventhandler;
	//eventhandler.setPlayer(player);
	
	CLevel *level;
	level = new CLevel;
	
	level->loadDataFromFile("data/maps/1.lvl");
	
	cout << level->getTitle() << endl;

	CBall *ball;
	ball = new CBall;
	ball->setCoords(level->getStartPoint());
	
	camera.setViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_W, VIEWPORT_H);
	/**************
	** game loop **
	**************/
	SDL_Event event;
	
	
	bool mouseDown = false;
	int mouseX = 0;
	int mouseY = 0;
	while(!quit) {
		// FPS
		startTime = SDL_GetTicks();
		
		/**************************************
		** event handling & processing stuff **
		**************************************/
		//player->stop();
		
			
		while (SDL_PollEvent(&event)) {  // we need a while loop as there may be several events in the queue
			switch (event.type) {
				case SDL_QUIT:
					quit = 1;
					break;
					
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						
						// do some shit based on the fact the mouse has been pressed
						if (ball->isPointInside(camera.x2a(event.button.x), camera.y2a(event.button.y))) {
							ball->startFling(event.button.x, event.button.y);
						}
						
						mouseDown = true;
					}
					break;
					
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (ball->isFlinging()) {
							ball->stopFling(event.button.x, event.button.y);	// launch sucker!
						}
						mouseDown = false;
					}
					break;
								
				case SDL_MOUSEMOTION:
					mouseX = event.motion.x;
					mouseY = event.motion.y;
					break;
			}
		}
		
		if (keyPressed(SDLK_ESCAPE)) {
			quit = 1;
			break;
		}

		/*********************
		** game logic stuff **
		*********************/
		
		//player->move();  // this takes care of bound checking
		
		//player->doThinks();  // basically amounts to weapon firing / bullets and stuff
		
		//world->doEntityThinks();
			
		
		
		/*
		SDL_Rect rect;
		rect.x = VIEWPORT_X;
		rect.y = VIEWPORT_Y;
		rect.w = VIEWPORT_W;
		rect.h = VIEWPORT_H;
		SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 255));	// white game area
		*/
		
		
		//ball->think();	// any pre move stuff
		
		ball->move(level);
		
		if (ball->cameraX() < (VIEWPORT_X + CAMERA_MOVE_THRESHOLD)) {
			int ox = (VIEWPORT_X + CAMERA_MOVE_THRESHOLD) - ball->cameraX();
			camera.translate(ox, 0);
		} else if (ball->cameraX() > (VIEWPORT_W - CAMERA_MOVE_THRESHOLD)) {
			int ox = ball->cameraX() - (VIEWPORT_W - CAMERA_MOVE_THRESHOLD);
			camera.translate(-ox, 0);
		}
		
		if (ball->cameraY() < (VIEWPORT_Y + CAMERA_MOVE_THRESHOLD)) {
			int oy = (VIEWPORT_Y + CAMERA_MOVE_THRESHOLD) - ball->cameraY();
			camera.translate(0, oy);
		} else if (ball->cameraY() > (VIEWPORT_H - CAMERA_MOVE_THRESHOLD)) {
			int oy = ball->cameraY() - (VIEWPORT_H - CAMERA_MOVE_THRESHOLD);
			camera.translate(0, -oy);
		}
		
		/********************
		** rendering stuff **
		********************/
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));  // white layer
		
		level->render();
		ball->render();
		if (ball->isFlinging()) {
			int x1 = ball->getFlingX();
			int y1 = ball->getFlingY();
			int x2 = mouseX;
			int y2 = mouseY;
			lineRGBA(screen, x1, y1, x2, y2, 128, 128, 255, 255);
		}
		
		SDL_Rect gui;
		gui.x = VIEWPORT_W;
		gui.y = VIEWPORT_Y;
		gui.w = SCREEN_W - VIEWPORT_W;
		gui.h = VIEWPORT_H;
		SDL_FillRect(screen, &gui, SDL_MapRGB(screen->format, 0, 0, 0));  // black layer
		//world->renderBackground(player->getAngle());
		//player->render(fps);  // render our view first (and render some bullets and that)
		
		//world->render();  // render the world (this actually only renders the top down map)
		//player->renderOnMap();
		//player->think();
		
		// draw hud
		//hud->draw();

		// write fps counter
		//hud->drawFPS(fps);
		
		SDL_Flip(screen);  // flip back buffer -> screen
		
		//SDL_framerateDelay(fpsman);
		
		frameTime = SDL_GetTicks()-startTime;
		fps = (frameTime>0) ? 1000 / frameTime : 0;
		SDL_Delay(25);
	}
	
	delete ball;
	delete level;

	cout << "Exiting..." << endl;
	SDL_Quit();
	cout << "Done." << endl;
	return 0;
}

bool keyPressed(SDLKey key)
{
	Uint8* keyState = SDL_GetKeyState(NULL);
	
	if(key < 0 || key >= 322)
	{
		return false;
	}
	
	return keyState[key];
}
