//
// C++ Interface: ball
//
// Description: 
//
//
// Author: Nick Payne <nick@kurai.co.uk>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef INC_BALL_H
#define INC_BALL_H
#include <SDL/SDL.h>
#include "level.h"

class CBall {
	public:
		CBall();
		~CBall();
		bool isPointInside(float px, float py);
		void move(CLevel *);
		void render();
		bool setColour(int, int, int);
		void setCoords(Point p);
		void startFling(int, int);
		void stopFling(int, int);
		
		bool isFlinging();
		int getFlingX();
		int getFlingY();
		
		int cameraX();
		int cameraY();

	private:
		float x;
		float y;

		float vx;
		float vy;

		int r;
		
		int cr;
		int cg;
		int cb;
		
		bool flinging;	// dragging a fling?
		int fX;	// fling X
		int fY;	// fling Y
};
		
#endif