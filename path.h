//
// C++ Interface: path
//
// Description: 
//
//
// Author: Nick <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef INC_PATH_H
#define INC_PATH_H
#include <SDL/SDL.h>
#include "globals.h"

class CPath {
	public:
		CPath();
		void setColour(int);
		bool addPoint(int, int);
		void render();
	private:
		int colour;
		int length;	// number of points
		Point points[100];	// each path can be up to 100 points long
		SDL_Rect bounds;	// when we load each path, we'll cache it's min / max bounds
};

#endif